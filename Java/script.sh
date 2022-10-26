WHERE=$(pwd)
cd $WHERE
javac septica.java
for i in {1..100}
do
	java Main
done
