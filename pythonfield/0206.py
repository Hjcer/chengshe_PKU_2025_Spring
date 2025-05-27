year = int(input())

if (year % 4 != 0) or (year % 100 == 0 and year % 400 != 0) or (year % 3200 == 0):
    print("N")
else:
    print("Y")