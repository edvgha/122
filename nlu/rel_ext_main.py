from collections import Counter
import os
import rel_ext
import utils

utils.fix_random_seeds()

rel_ext_data_home = os.path.join('data', 'rel_ext_data')

corpus = rel_ext.Corpus(os.path.join(rel_ext_data_home, 'corpus.tsv.gz'))

kb = rel_ext.KB(os.path.join(rel_ext_data_home, 'kb.tsv.gz'))

dataset = rel_ext.Dataset(corpus, kb)

splits = dataset.build_splits()

def simple_bag_of_words_featurizer(kbt, corpus, feature_counter):
    for ex in corpus.get_examples_for_entities(kbt.sbj, kbt.obj):
        for word in ex.middle.split(' '):
            feature_counter[word] += 1
    for ex in corpus.get_examples_for_entities(kbt.obj, kbt.sbj):
        for word in ex.middle.split(' '):
            feature_counter[word] += 1
    return feature_counter


kbt = kb.kb_triples[0]

corpus.get_examples_for_entities(kbt.sbj, kbt.obj)[0].middle

simple_bag_of_words_featurizer(kb.kb_triples[0], corpus, Counter())

kbts_by_rel, labels_by_rel = dataset.build_dataset()

featurized = dataset.featurize(kbts_by_rel, featurizers=[simple_bag_of_words_featurizer])

train_result = rel_ext.train_models(
    splits,
    featurizers=[simple_bag_of_words_featurizer])

predictions, true_labels = rel_ext.predict(
    splits, train_result, split_name='dev')
