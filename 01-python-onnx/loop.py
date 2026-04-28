tree = 0
while tree < 10:
    print("tree is %d" % tree)
    tree += 1
    if tree == 10:
        print("tree is 10, stop counting")

prompt = """
1. Add
2. del
3. list
4. quit
Enter number: """

number = 0
while number != 4:
    number = int(input(prompt))
    if number == 1:
        print("Add")
    elif number == 2:
        print("del")
    elif number == 3:
        print("list")
    elif number == 4:
        print("quit")
    else:
        print("wrong number")

print ("program end")

while True:
    number = int(input(prompt))
    if number == 1:
        print("Add")
    elif number == 2:
        print("del")
    elif number == 3:
        print("list")
    elif number == 4:
        break
    else:
        print("wrong number")

print ("program end")
