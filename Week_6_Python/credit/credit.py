from sys import exit


def main():

    checkNumber(getCreditCardNumber())


def getCreditCardNumber():

    while True:
        card = input("Number: ")

        try:
            int(card)
            return card
        except:
            print("Please input a possible credit card number.")


def applyLuhnAlgo(num):

    part1 = 0
    control1 = len(num) - 1
    control2 = len(num) - 2
    valid = 0

    while (control2 >= 0):
        part1 += (int(num[control2]) * 2)
        control2 -= 2

    for i in str(part1):
        valid += int(i)

    while (control2 >= 0):
        valid += int(num[control1])
        control1 -= 2

    return (valid % 10)


# num here is received as str
def checkNumber(num):

    if (len(num) == 15) and (num[0:2] in "34,37"):
        if (applyLuhnAlgo(num)):
            print("AMEX")
            exit(0)
    elif (len(num) == 16) and (num[0:2] in "51,52,53,54,55"):
        if (applyLuhnAlgo(num)):
            print("MASTERCARD")
            exit(0)
    elif (len(num) == 16 or len(num) == 13) and (num[0] == "4"):
        if (applyLuhnAlgo(num)):
            print("VISA")
            exit(0)
    else:
        print("INVALID")
        exit(1)


main()