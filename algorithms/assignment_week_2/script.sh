#!/bin/bash

# Create the data file
cat <<EOF > employees.txt
Alice,Engineering,50,40
Bob,Marketing,35,38
Charlie,Engineering,60,45
David,HR,30,40
Eva,Engineering,55,35
EOF

# task 1
awk -F, '{print $1, $2}' employees.txt

# task 2
awk -F, '$2 == "Engineering"' employees.txt

# task 3
awk -F, '{print $1 " gross pay: $" $3 * $4}' employees.txt

# task 4
awk -F, '{print NR " (" NF " fields): " $0}' employees.txt

# task 5
awk -F, '
BEGIN { total = 0 }
$2 == "Engineering" { total += $3 * $4 }
END { print "Total Engineering Payroll: $" total }
' employees.txt
