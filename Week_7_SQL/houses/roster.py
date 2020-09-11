from sys import argv, exit
import cs50

if (len(argv) != 2):
    print("Incorrect use. Pass in the name of a house file only")
    exit(1)


db = cs50.SQL("sqlite:///students.db")

students = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first", argv[1])

for student in students:

    first_name = student["first"]
    middle_name = student["middle"]
    last_name = student["last"]
    birth = student["birth"]

    if (middle_name):
        print(f"{first_name} {middle_name} {last_name}, born {birth}")
    else:
        print(f"{first_name} {last_name}, born {birth}")

