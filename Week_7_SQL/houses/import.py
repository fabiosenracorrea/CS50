from sys import argv, exit
import cs50
import csv

if (len(argv) != 2):
    print("Incorrect use. Pass in a csv file only")
    exit(1)

db = cs50.SQL("sqlite:///students.db")

# db.execute("CREATE TABLE students (first_name TEXT, middle_name TEXT, last_name TEXT, birth NUMERIC, house TEXT)")

with open(argv[1], "r") as students:

    reader = csv.DictReader(students)

    for row in reader:

        name = row["name"].split(" ")

        first_name = name[0]
        birth = row["birth"]
        house = row["house"]

        if len(name) == 3:
            middle_name = name[1]
            last_name = name[2]
        else:
            last_name = name[1]
            middle_name = None

        db.execute("INSERT INTO students (first, middle, last, birth, house) VALUES (?, ?, ?, ?, ?)",
                    first_name, middle_name, last_name, birth, house)
