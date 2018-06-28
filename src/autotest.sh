if ./trivium-test; then exit 1
fi

echo
echo Testing files...
if ./trivium-test plain.in cipher.out; then
	if diff cipher.out empty.ref; then
		echo PASSED
	else exit 3
	fi
else exit 2
fi

echo
if ./trivium-test plain.in cipher.out test.key; then
	if diff cipher.out test.ref; then
		echo PASSED
	else exit 5
	fi
else exit 4
fi
