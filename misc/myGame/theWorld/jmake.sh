SRC=src
TARGET=target

TEST=test/testMyWorld.java

rm -rf target
mkdir target

javac $SRC/*.java -d $TARGET
javac $TEST -d $TARGET -cp $TARGET
