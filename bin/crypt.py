#!/usr/bin/env python3
from getpass import getpass
from sys import argv as sys_argv
from hashlib import sha256
from csv import reader

def main(argc, argv):
    # Generate from file
    if   argc == 2:
        keyword = getpass("Enter keyword: ")
        file = open(argv[1], mode="r")
        accounts = reader(file)
        for line in accounts:
            password = generate_password(line[0], line[1], line[2], line[3], keyword)
            print("/--------------------------------%s\n%s\n%s\n" % (line[0], line[1], password))
        file.close()
    # Generate single
    elif argc == 5:
        keyword = getpass("Enter keyword: ")
        password = generate_password(argv[1], argv[2], argv[3], argv[4], keyword )
        print( "/--------------------------------%s\n%s\n%s\n" % (argv[1], argv[2], password) )

    else:
        print("Usage:\n\tcrypt.py service username length special\n\tcrypt.py /address/to/csv/file")
        quit()


    response = input("Press return to quit...")
    quit()

def sha256sum(string):
    hasher = sha256()
    hasher.update(string.encode('utf-8'))
    return hasher.hexdigest()

charactors = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*"
def generate_password(service, username, length, special, keyword):
    # ------------------------------------------------------------------------- Converts inputs to 256 hashes
    hashes = [
        sha256sum(service),
        sha256sum(username),
        sha256sum(length),
        sha256sum(special),
        sha256sum(keyword)
    ]
    # --------------------------------------------------------- Zips 256 hashes together into a single string
    hash_string = ""

    for i in range(64):
        hash_string += "%c%c%c%c%c" % (hashes[0][i], hashes[1][i], hashes[2][i], hashes[3][i], hashes[4][i])
   # ------------------------------------------------------------------------------- Gets initial seed value
    seed_value = 0
    for c in hash_string:
        seed_value += ord(c)
    # ----------------------------------------------------------------------------------- Sets range
    flags = [0,0,0,0] #lower, upper, numbers, special
    cap = 70

    if special != "true":
        cap = 62
        flags[3] = 1
    # ------------------------------------------------------------------------- Generates a password
    password = ""
    attempt = 0

    while (password == ""):
        attempt += 1

        for i in range(int(length)):
            seed_value += ord(hash_string[i])
            capped_seed_value = seed_value % cap

            if   capped_seed_value <= 25:
                flags[0] += 1

            elif capped_seed_value >= 26 and capped_seed_value <= 51:
                flags[1] += 1

            elif capped_seed_value >= 52 and capped_seed_value <= 61:
                flags[2] += 1

            elif capped_seed_value % cap >= 62:
                flags[3] += 1

            password += charactors[capped_seed_value]
    # -------------------------------------------------------------------- Returns if attempt is 100
        if attempt >= 100:
            return password
    # ------------ Checks flags to ensure password has at least one lower, upper, numeric and symbol
        for flag in flags:
            if flag < 1:
                password = ""

                if special != "true":
                    flags = [0,0,0,1]
                else:
                    flags = [0,0,0,0]

    return password

main(len(sys_argv), sys_argv)
