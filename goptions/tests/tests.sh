#!/bin/zsh

# simpleExample

tests=(simpleExampleBothDefined simpleExampleDefaultMissing simpleExampleEmptyJcard simpleExampleOneSameAsDefault simpleExampleEmptyJcard )

echo

if [[ $1 = 'reset' ]]; then

	echo " Resetting no jcard"
	check=tests/simpleExampleNoJcard.txt
	$(./simpleExample > $check)

	for t in $tests
	do
		echo " Resetting " $t
		jcard=tests/$t".jcard"
		check=tests/$t".txt"
		rm $check
		$(./simpleExample $jcard > $check)
	done

else

	# performing tests


	# first running w/o jcard
	check=tests/simpleExampleNoJcard.txt
	a=$(./simpleExample)
	b=$(cat $check)
		if [[ "$a" = "$b" ]]; then
			echo " - no jcard: success"
		else
			echo " - no jcard: fail"
			echo ---
			echo $a
			echo ---
			echo $b
			echo ---
		fi

	for t in $tests
	do
		jcard=tests/$t".jcard"
		check=tests/$t".txt"
		a=$(./simpleExample $jcard)
		b=$(cat $check)
		if [[ "$a" = "$b" ]]; then
			echo " - "$t": success"
		else
			echo " - "$t": fail"
			echo ---
			echo $a
			echo ---
			echo $b
			echo ---
		fi
	done

fi




echo
