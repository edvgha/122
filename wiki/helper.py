import alphabet

fp = open('/home/edvard/122/glove1/output/arm_vocab.txt', 'r')
fo1 = open("vocab_no_word.txt", "w")
fo2 = open("vocab_word.txt", "w")
line = fp.readline()
while line:
    l = line.split()
    if not alphabet.is_arm_shallow_word(l[0]):
        fo1.write(l[0])
        fo1.write('\n')
    else:
        fo2.write(l[0])
        fo2.write('\n')
    line = fp.readline()
fp.close()
fo1.close()
fo2.close()
