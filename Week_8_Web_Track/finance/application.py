import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():

    user = session["user_id"]

    user_stocks = db.execute("SELECT * FROM stock_count WHERE user_id = :id AND overall_quantity > 0", id=user)
    user_cash = float(db.execute("SELECT * FROM users WHERE id = :id", id=user)[0]["cash"])
    total_in_stocks = 0

    for i, stock in enumerate(user_stocks):
        results = lookup(stock["stock"])
        current_pricing = float(results["price"])
        total_in_stocks += current_pricing
        stock["price"] = current_pricing
        if i % 2 == 0:
            stock["class"] = "grey-bg"
        else:
            stock["class"] = "normal-bg"

    return render_template("index.html", stocks=user_stocks, total=(user_cash + total_in_stocks), cash=user_cash)



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html", std=True)

    stock = request.form.get("stock")
    quantity = int(request.form.get("qtd"))

    results = lookup(stock)

    if not results:
        return render_template("buy.html", notfound=True)

    user = session["user_id"]

    user_info = db.execute("SELECT * FROM users WHERE id = :user_id", user_id=user);

    current_balance = user_info[0]["cash"]

    if (current_balance < results["price"] * quantity):
        return apology("Insufficient founds", 400)

    new_balance = current_balance - (results["price"] * quantity)

    db.execute("UPDATE users SET cash = :new", new=new_balance)
    db.execute("INSERT INTO stock_operations (type, user_id, stock, price, quantity) VALUES (:t, :user_id, :stock, :price, :qtd)", t="buy", user_id=user, stock=stock, price=results["price"], qtd=quantity)

    user_existant_stocks = db.execute("SELECT * FROM stock_count WHERE user_id = :id AND stock = :stock", id=user, stock=stock)

    try:
        if user_existant_stocks[0]:
            new_quantity = int(user_existant_stocks[0]["overall_quantity"]) + quantity
            db.execute("UPDATE stock_count SET overall_quantity = :qtd WHERE user_id = :id", qtd=new_quantity, id=user)
    except:
        db.execute("INSERT INTO stock_count (user_id, stock, overall_quantity, company_name) VALUES (:id, :stock, :qtd, :name)", id=user, stock=stock, qtd=quantity, name=results["name"])

    return redirect("/")


@app.route("/history")
@login_required
def history():

    user = session["user_id"]

    transactions = db.execute("SELECT * FROM stock_operations WHERE user_id = :id", id=user)

    if len(transactions) == 0:
        return render_template("history.html")

    for i, stock in enumerate(transactions):
        if i % 2 != 0 and stock["type"] == "buy":
            stock["class"] = "grey-bg-red-text"
        elif i % 2 == 0 and stock["type"] == "buy":
            stock["class"] = "normal-bg-red-text"
        elif i % 2 != 0 and stock["type"] == "sell":
            stock["class"] = "grey-bg-green-text"
        else:
            stock["class"] = "normal-bg-green-text"


    return render_template("history.html", history=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return render_template("login.html", warning="enter your username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return render_template("login.html", warning="enter your password")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return render_template("login.html", warning="Wrong password")

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():

    if request.method == "GET":
        return render_template("quote.html")

    stock = request.form.get("stock")

    results = lookup(stock)

    if not results:
        return render_template("quote.html", notfound=True, price=1)

    return render_template("quote.html", companyName=results["name"], price=results["price"])


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")

    username = request.form.get("username")
    inputPw = request.form.get("password");
    confirmation = request.form.get("confirmation");

    if not username:
        return render_template("register.html", warning="must provide an username")
    elif not inputPw:
        return render_template("register.html", warning="must provide a password")
    elif inputPw != confirmation:
        return render_template("register.html", warning="passwords must match")

    userExists = db.execute("SELECT * FROM USERS WHERE username = :username", username=username)

    if (len(userExists) > 0):
        return render_template("register.html", warning="Username already exists")

    password = generate_password_hash(inputPw)

    db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=username, hash=password)

    return redirect("/login")

@app.route("/change-pw", methods=["GET", "POST"])
@login_required
def change_pw():

    if request.method == "GET":
        return render_template("change-pw.html")

    user = session["user_id"]

    oldPW = request.form.get("old")
    newPw = request.form.get("new");
    confirmPw = request.form.get("confirmation");

    user_info = db.execute("SELECT * FROM users WHERE id = :id", id=user)

    if not check_password_hash(user_info[0]["hash"], oldPW):
        return render_template("change-pw.html", warning="Incorrect previous password")

    if newPw != confirmPw:
        return render_template("change-pw.html", warning="New password and confirmation don't match")

    password = generate_password_hash(newPw)

    db.execute("UPDATE users SET hash = :pw WHERE id = :id", pw=password, id=user)

    return redirect("/")


@app.route("/deposit", methods=["GET", "POST"])
@login_required
def deposit():

    if request.method == "GET":
        return render_template("deposit.html")

    user = session["user_id"]

    amount = float(request.form.get("deposit"))

    user_info = db.execute("SELECT * FROM users WHERE id = :id", id=user)

    new_amount = float(user_info[0]["cash"]) + amount

    db.execute("UPDATE users SET cash = :new WHERE id = :id", new=new_amount, id=user)

    return render_template("deposit.html", success=amount)


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():

    user = session["user_id"]

    # quering to determine the amount available
    stocks = db.execute("SELECT * FROM stock_count WHERE user_id = :id", id=user)

    if request.method == "GET":
        return render_template("sell.html", std=True, stocks=stocks)

    # lets check what and how many the user wants to sell
    stock = request.form.get("stock")
    quantity = int(request.form.get("qtd"))

    current = db.execute("SELECT * FROM stock_count WHERE user_id = :id AND stock = :stock", id=user, stock=stock)
    available_stocks = int(current[0]["overall_quantity"])

    if (available_stocks - quantity < 0):
        return render_template("sell.html")

    # the user has balance to sell, let's do it!
    results = lookup(stock)

    sold_amount = int(results["price"]) * quantity

    old_balance = db.execute("SELECT * FROM users WHERE id = :id", id=user)

    new_balance = int(old_balance[0]["cash"] + sold_amount)

    db.execute("UPDATE users SET cash = :new WHERE id = :id", new=new_balance, id=user)
    db.execute("INSERT INTO stock_operations (type, user_id, stock, price, quantity) VALUES (:t, :user_id, :stock, :price, :qtd)", t="sell", user_id=user, stock=stock, price=sold_amount, qtd=quantity)

    new_quantity = int(stocks[0]["overall_quantity"]) - quantity

    db.execute("UPDATE stock_count SET overall_quantity = :qtd WHERE user_id = :id", qtd=new_quantity, id=user)


    return render_template("sell.html", sold=True, quantity=quantity, value=sold_amount, code=stock)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
