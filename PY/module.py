# task 1

def sum_for(num_list):
    result = 0
    for i in num_list:
        result = result + i
    return result


def sum_while(num_list):
    result = 0
    counter = 0
    while counter < len(num_list):
        result += num_list[counter]
        counter += 1
    return result


def sum_recursion(num_list):
    if len(num_list) == 1:
        return num_list[0]
    else:
        return num_list[0] + sum_recursion(num_list[1::])

print(sum_for(range(5)))
print(sum_while(range(5)))
print(sum_recursion(range(5)))

# end of task 1
# task 2


def word(s):
    s = s.lower()
    if s.isalpha():
        vowels = set('aeoyui')
        print(''.join([f'.{x}' for x in s if x not in vowels]))
    else:
        print("The input has numbers or punctuation.")


line = input("Enter your word: ", )
word(line)

# end of task 2
# task 3


def identical_elements(a, b):
    result1 = []
    result2 = []

    for i in a:
        if i in b:
            result1.append(i)

    for i in a:
        if i not in b:
            result2.append(i)

    print("intersection of A and B: ", sorted(result1))
    print("A - B: ", sorted(result2))


identical_elements(list(map(int, input("List 1: ").split())), list(map(int, input("List 1: ").split())))

# end of task 3
# task 4


def letter_counter(w):
    result = {}
    w = w.lower()

    for char in w:
        if char.isalpha():
            result[char] = w.count(char)
    print(result)


letter_counter(input("Enter your word: "))

# end of task 4
# task 5


def checkPassword(pswd):
   return len(pswd) >= 10 \
          and sum(chr.isdigit() for chr in pswd) >= 3 \
          and sum(chr.isupper() for chr in pswd) >= 1 \
          and len([1 for i in pswd if i in "!@#$%*"]) >= 1


password = input("Password: ")
if checkPassword(password):
    print(password + " Perfect password")
else:
    print(password + " Easy peasy")


# end of task 5
# task 6

def uniq_char(line):
    cur_index = 0
    for i in line:
        if line.count(i) == 1:
            return cur_index
        cur_index += 1
    return -1


print(uniq_char("python"))
print(uniq_char("abracadabra"))
print(uniq_char("abcabc"))

# end of task 6
# task 7

def calc_arg_num(*args):
    return len(args)


print(calc_arg_num(1, 2, "word"))

# end of task 7
# task 8

def print_goods(*goods):
    index = 1
    for good in goods:
        if isinstance(good, str):
            print(str(index) + " " + good)
            index += 1
    if index == 1:
        print("Немає товарів")


print_goods('apple', 'banana', 'orange')
print_goods(1, True, 'Груша', '', 'Яблуко')
print_goods([], {}, 1, 2)

# end of task 8
# task 9

def flatten(items):
    result = []
    for i in items:
        if isinstance(i, list):
            result += flatten(i)
        else:
            result.append(i)
    return result


print(flatten([1, [2, 3, [4]], 5]))
print(flatten([1, [2,3], [[2], 5], 6]))
print(flatten([[[[9]]], [1, 2], [[8]]]))

# end of task 9
# task 10

def test():
    l = lambda input: l(input)

# end of task 10
