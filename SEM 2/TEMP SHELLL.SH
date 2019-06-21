#!/bin/sh
# FILE PATH 

# Output Formatting Line
line()
{
	echo "====================================="
}

# FILE FUNCTIONS
CreateFile()
{
	echo "Enter File Name"
	read filename
	touch $filename
	echo "File Created Successfully ! at $name"
}

AddRecord()
{
	if [ -z "$filename" ]
	then
		echo "NO FILE Found !"
		return 
	fi
	echo "Enter the Details of Student"
    echo "Name "
	read name
	echo "Roll No"
	read roll 
	echo "class"
	read class
	echo "$name $roll $class" >> "$filename"
}

# MAIN 

# MENU
while :
do 
	line
	echo "File Managment System"
	echo "\n1) Create a new file"
	echo "2) Display File"
	echo "3) Add Record"
	echo "4) Search"
	echo "5) Delete"
	echo "6) Modify"
	echo "7) Exit"
	echo "\nYour Choice : "
	read Choice
	line

		case $Choice in
			1) CreateFile;;  
			2) if [ -z "$filename" ]
				then
					echo "NO FILE Found !"
				else
					echo "FILE NAME : $filename\n"
			   		cat $filename
				fi;;
				
			3) AddRecord;;
			4) ;;
			5) ;;
			6) ;;
			7) Exit;;
			*) echo "Default" ;;
		esac
done
line
