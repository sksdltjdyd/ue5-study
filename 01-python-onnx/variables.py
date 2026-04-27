# number
a = 1
b = 2.5
c = a + b
print(c)

# string
d = "hello"
e = "12.4"
f = d + " number is " + e
g = 'hello"dsde'
tail = "tail"
word = "i have %d %s" %(3, "dogs") # string formatting
name = "Lee"
age = 30
one = f"My name is {name} and I am {age} years old." # f-string
print(f)
print(g)
print(tail[0:2]) # indexing
print(word)
print(one)
print(tail.upper()) # string metho
print(tail.count("a")) # count occurrences of "a"
print(tail.replace("a", "o")) # replace "a" with "o"

# list
h = [1, 2, 3, 4, 5]
i = ["a", "b", "c", "d", "e"]
del h[0] # delete first element
j = [1, "a", 2.5, [1, 2], {"key": "value"}] # list can contain different types
print(h)
print(i)
print(j)
print(len(h))
del j[2:]
print(j)
h.append(6) # add element to end of list
print(h)
h.sort(reverse=True) # sort list in reverse order
print(h)