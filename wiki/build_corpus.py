import os
import argparse
import alphabet
import Tokenizer.tokenizer
from collections import defaultdict
import csv

#############################################
#                   Root Dir                #
#                      |                    #
#         +------------+------------+       #
#         |            |            |       #
#       Sub Dir1     Sub Dir2    Sub Dir3   #
#         |            |            |       #
#    +----+----+  +----+----+  +----+----+  #
#    |    |    |  |    |    |  |    |    |  #
# Page1 ...     Page1 ...    Page1 ...      #
#############################################

parser = argparse.ArgumentParser()
parser.add_argument('--root_directory', type=str, help="root directory with subdirecotires", default='ARM')
parser.add_argument('--out_file_name', type=str, help="corpus file name", default='corpus')

def corpus_builder(root_dir_path, out_file_name):
    print('Started from {0} ...'.format(root_dir_path))
    if not os.path.isdir(root_dir_path):
        print('{0} is not a directory'.format(root_dir_path))
        return
    if os.path.exists(out_file_name):
        print('Removed old corpus: {0}'.format(out_file_name))
        os.remove(out_file_name)
        os.remove(out_file_name + '_new')
    corpus = open(out_file_name, 'a+')
    new_corpus = open(out_file_name + '_new', 'a+')
    count = 0
    tokens = defaultdict(int)
    for sub_dir in os.listdir(root_dir_path):
        for file in os.listdir(root_dir_path + '/' + sub_dir):
            with open(root_dir_path + '/' + sub_dir + '/' + file, 'r') as infile:
                tk = Tokenizer.tokenizer.Tokenizer(infile.read())
                tk.segmentation()
                tk.tokenization()
                output = tk.output()
                c = ''
                for el in output:
                    segment = el['segment']
                    corpus.write(segment)
                    for token in el['tokens']:
                        t = alphabet.trim(token[1])
                        if alphabet.is_arm_word(t):
                            c += t + ' '
                            tokens[t] += 1
                new_corpus.write(c)
                count += 1
    print('Processed {0} files'.format(count))
    print('Corpus is in {0}'.format(out_file_name))
    print('Corpus is in {0}'.format(out_file_name + '_new'))
    corpus.close()
    new_corpus.close()
    with open('tokens.csv', 'w') as f:
        fieldnames = ['token', 'count']
        writer = csv.DictWriter(f, fieldnames)
        for k, v in tokens.items():
            writer.writerow({'token':k, 'count':v})

if __name__ == '__main__':
    args = parser.parse_args()
    corpus_builder(args.root_directory, args.out_file_name)
