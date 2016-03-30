set SRC=src
set TARGET=target

set TEST=test/testMyWorld.java

rmdir/S target
mkdir target

javac %SRC%/*.java -d %TARGET%
javac %TEST% -d %TARGET% -cp %TARGET%
