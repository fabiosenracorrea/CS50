def main():
    printBlocks(getHeight())


def getHeight():
    while True:
        height = input("Height: ")

        try:
            height = int(height)
            if (height > 0) and (height < 9):
                return height
            else:
                continue
        except:
            continue


def printBlocks(n):
    for i in range(1, n+1):
        baseL = " " * (n - i) + "#" * (i)
        baseR = "#" * (i)
        print(f"{baseL}  {baseR}")


main()