#!/bin/sh -e

data_url=https://cryptopals.com/static/challenge-data/4.txt

make set_1_challenge_4

top_lines()
{
	./set_1_challenge_3 "$1" \
		| sort -nr \
		| head -5
}

score_lines()
{
	count=0
	while read line
	do
		top_lines "$line" | while read result
		do
			echo "$result	$count"
		done
		count=$(( count + 1 ))
	done
}


main()
{
	wget -O - "$data_url" \
		| score_lines \
		| sort -nr \
		| head -1
}

main
