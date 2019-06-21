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
	echo "File Created / Opened Successfully !"
}

AddRecord()
{
	# Basic Validation
	if [ -z "$filename" ]
	then
		echo "NO FILE Found !"
		return 
	fi

	# Taking Input from User for new Entry
	echo "Enter the Details of Student"
    echo "Name "
	read name
	echo "Roll No"
	read roll 
	echo "class"
	read class
	echo "$name $roll $class" >> "$filename"
}

SearchRecord()
{
	# Basic Validation
	if [ -z "$filename" ]
	then
		echo "NO FILE Found !"
		return 
	fi

	echo "Enter The Name Or Roll No of Student You Want to Search"
	read pattern
	grep -r $pattern $filename
}

DeleteRecord()
{
	# Basic Validation
	if [ -z "$filename" ]
	then
		echo "NO FILE Found !"
		return 
	fi
	echo "Enter the Roll or Name No you want to be removed"
	read pattern
	sed -i "/\b\ $pattern \b/d" $filename
	# Refer 
	# https://askubuntu.com/questions/354993/how-to-remove-lines-from-the-text-file-containing-specific-words-through-termina
}

ModifyRecord()
{
	# Basic Validation
	if [ -z "$filename" ]
	then
		echo "NO FILE Found !"
		return 
	fi

	echo "Enter the Name / Roll No of Student You Want to Modify"
	read pattern
	echo "Name "
	read name
	echo "Roll No"
	read roll 
	echo "class"
	read class
	sed -i "/$pattern/c\ $name $roll $class" $filename


}
# MAIN 

# MENU
while :
do 
	line
	echo "File Managment System"
	echo "\n1) Create a new file / Open Existing File"
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
				
			3) # Add A Loop To Accept Multiple records 
				AddRecord;;
				
			4) SearchRecord;;
			5) DeleteRecord;;
			6) ModifyRecord;;
			7) exit;;
			*) echo "Default" ;;
		esac
done
line
