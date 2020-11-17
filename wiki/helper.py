import alphabet
import csv

fo1 = open("vocab_no_word.txt", "w")
fo2 = open("vocab_word.txt", "w")

with open('tokens.csv', newline='\n') as csvfile:
    reader = csv.reader(csvfile, delimiter=",")
    for row in reader:
        if alphabet.is_arm_word(row[0]):
            fo2.write(row[0])
            fo2.write('\n')
        else:
            fo1.write(row[0])
            fo1.write('\n')

fo1.close()
fo2.close()
