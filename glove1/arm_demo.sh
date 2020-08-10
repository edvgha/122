#!/bin/bash
set -e

OUTPUT=output
CORPUS=merged_file
VOCAB_FILE=arm_vocab.txt
COOCCURRENCE_FILE=arm_cooccurrence.bin
COOCCURRENCE_SHUF_FILE=arm_cooccurrence.shuf.bin
BUILDDIR=build
SAVE_FILE=arm_vectors
VERBOSE=2
MEMORY=4.0
VOCAB_MIN_COUNT=5
VECTOR_SIZE=50
MAX_ITER=15
WINDOW_SIZE=15
BINARY=2
NUM_THREADS=8
X_MAX=10
PYTHON=python3
EVALS=eval_cos_dist

echo
echo "$ $BUILDDIR/vocab_count -min-count $VOCAB_MIN_COUNT -verbose $VERBOSE < $CORPUS > $OUTPUT/$VOCAB_FILE"
$BUILDDIR/vocab_count -min-count $VOCAB_MIN_COUNT -verbose $VERBOSE < $CORPUS > $OUTPUT/$VOCAB_FILE
echo "$ $BUILDDIR/cooccur -memory $MEMORY -vocab-file $OUTPUT/$VOCAB_FILE -verbose $VERBOSE -window-size $WINDOW_SIZE < $CORPUS > $OUTPUT/$COOCCURRENCE_FILE"
$BUILDDIR/cooccur -memory $MEMORY -vocab-file $OUTPUT/$VOCAB_FILE -verbose $VERBOSE -window-size $WINDOW_SIZE < $CORPUS > $OUTPUT/$COOCCURRENCE_FILE
echo "$ $BUILDDIR/shuffle -memory $MEMORY -verbose $VERBOSE < $OUTPUT/$COOCCURRENCE_FILE > $OUTPUT/$COOCCURRENCE_SHUF_FILE"
$BUILDDIR/shuffle -memory $MEMORY -verbose $VERBOSE < $OUTPUT/$COOCCURRENCE_FILE > $OUTPUT/$COOCCURRENCE_SHUF_FILE
echo "$ $BUILDDIR/glove -save-file $OUTPUT/$SAVE_FILE -threads $NUM_THREADS -input-file $OUTPUT/$COOCCURRENCE_SHUF_FILE -x-max $X_MAX -iter $MAX_ITER -vector-size $VECTOR_SIZE -binary $BINARY -vocab-file $OUTPUT/$VOCAB_FILE -verbose $VERBOSE"
$BUILDDIR/glove -save-file $OUTPUT/$SAVE_FILE -threads $NUM_THREADS -input-file $OUTPUT/$COOCCURRENCE_SHUF_FILE -x-max $X_MAX -iter $MAX_ITER -vector-size $VECTOR_SIZE -binary $BINARY -vocab-file $OUTPUT/$VOCAB_FILE -verbose $VERBOSE
echo "$ $PYTHON eval/python/distance.py"
$PYTHON eval/python/distance.py > $OUTPUT/$EVALS
