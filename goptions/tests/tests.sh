#!/bin/zsh

# simpleExample

tests=(simpleExampleBothDefined simpleExampleDefaultMissing simpleExampleEmptyJcard simpleExampleOneSameAsDefault simpleExampleEmptyJcard )

echo

if [[ $1 = 'reset' ]]; then

	echo " Resetting no jcard"
	check1=tests/simpleExampleNoJcard.txt
	check2=tests/simpleExampleNoJcardWithGui.txt
	$(./simpleExample      > $check1)
	$(./simpleExample -gui > $check2)

	for t in $tests
	do
		echo " Resetting " $t
		jcard=tests/$t".jcard"
		check1=tests/$t".txt"
		check2=tests/$t"WithGui.txt"
		rm $check1 $check2
		$(./simpleExample $jcard      > $check1)
		$(./simpleExample $jcard -gui > $check2)
	done

else

	# performing tests


	# first running w/o jcard
	check1=tests/simpleExampleNoJcard.txt
	check2=tests/simpleExampleNoJcardWithGui.txt
	a1=$(./simpleExample)
	a2=$(./simpleExample -gui)
	b1=$(cat $check1)
	b2=$(cat $check2)
	if [[ "$a1" = "$b1" ]]; then
		echo " - no jcard: success"
	else
		echo " - no jcard: fail"
		echo ---
		echo $a1
		echo ---
		echo $b1
		echo ---
	fi
	if [[ "$a2" = "$b2" ]]; then
		echo " - no jcard with gui: success"
	else
		echo " - no jcard with gui: fail"
		echo ---
		echo $a2
		echo ---
		echo $b2
		echo ---
	fi

	for t in $tests
	do
		jcard=tests/$t".jcard"
		check1=tests/$t".txt"
		check2=tests/$t"WithGui.txt"
		a1=$(./simpleExample $jcard)
		a2=$(./simpleExample $jcard  -gui)
		b1=$(cat $check1)
		b2=$(cat $check2)
		if [[ "$a1" = "$b1" ]]; then
			echo " - "$t": success"
		else
			echo " - "$t": fail"
			echo ---
			echo $a1
			echo ---
			echo $b1
			echo ---
		fi
		if [[ "$a2" = "$b2" ]]; then
			echo " - "$t" with gui: success"
		else
			echo " - "$t" with gui: fail"
			echo ---
			echo $a2
			echo ---
			echo $b2
			echo ---
		fi
	done

fi




echo
