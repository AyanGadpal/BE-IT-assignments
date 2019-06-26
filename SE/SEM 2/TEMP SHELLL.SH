#!/bin/sh

#====================================================
# Auther     : Ayan N Gadpal 33308
# Script     : File Operations Using Bash Shell Scripting
# Date       : Jun 25 2019 / 10 am
# Copy Right : GNU public Library
#====================================================

# Output Formatting Line
line()
{
	echo "======================================================="
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
		echo "\t\t ERROR :: NO FILE FOUND ,ENTER THE FILE NAME !"
		CreateFile 
	fi

	# Taking Input from User for new Entry
	echo "Enter the Details of Student"
    echo "Name "
	read name
	echo "Roll No"
	read roll 
	echo "class"
	read class
	echo "|\t $name    \t|\t $roll \t|\t $class" >> "$filename"
}

SearchRecord()
{
	# Basic Validation
	if [ -z "$filename" ]
	then
		echo "\t\t ERROR :: NO FILE FOUND ,ENTER THE FILE NAME !"
		CreateFile 
	fi

	echo "Enter The Name Or Roll No of Student You Want to Search"
	read pattern
	grep -r -w $pattern $filename
	result=$( grep -r -w $pattern $filename ) 
	if [ -n "$result" ] ;
	then
		echo "Found"
	else
		echo "Not Found"
	fi
}

DeleteRecord()
{
	# Basic Validation
	if [ -z "$filename" ]
	then
		echo "\t\t ERROR :: NO FILE FOUND ,ENTER THE FILE NAME !"
		CreateFile 
	fi
	echo "Enter the Roll or Name No you want to be removed"
	read pattern
	sed -i "/\\$pattern/d" $filename
}

ModifyRecord()
{
	# Basic Validation
	if [ -z "$filename" ]
	then
		echo "\t\t ERROR :: NO FILE FOUND ,ENTER THE FILE NAME !"
		CreateFile 
	fi

	echo "Enter the Name / Roll No of Student You Want to Modify"
	read pattern
	echo "Name "
	read name
	echo "Roll No"
	read roll 
	echo "class"
	read class
	sed -i "/$pattern/c\|\t $name    \t|\t $roll \t|\t $class" $filename
}

DisplayFile()
{
	if [ -z "$filename" ]
	then
		echo "NO FILE Found !"
	else
	echo "FILE NAME : $filename\n"
	echo "-------------------------------------------------------"
	echo "|\t NAME    \t|\tRoll No.|\t Class"
	echo "-------------------------------------------------------"
	cat $filename
	fi
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
			# Create The File or Open an Existing File
			1) CreateFile;;  

			# Display the File 
			2) DisplayFile;;
				
			# Enter the Records
			3) echo "Enter the number of records to be inserted : "
			   read num
			   while [ $num -ne 0 ]
			   do
			   	    num=`expr $num - 1`
			   		AddRecord
			   		line
			   done;;
			
			# Search Some Record Within The File
			4) SearchRecord;;

			# Delete Some Record from the File
			5) DeleteRecord;;

			# Modify the Record of the File
			6) ModifyRecord;;

			# Exit
			7) exit;;

			# Inproper Option Handling
			*) echo "ERROR :: Please Enter the Proper Option for 1 to 7." ;;
		esac
done
line


# REFERNCES 
# DELETE : https://askubuntu.com/questions/354993/how-to-remove-lines-from-the-text-file-containing-specific-words-through-termina
# Basic OPeration : https://www.tutorialspoint.com/unix/unix-basic-operators.htm
# Rest of Script  : https://www.shellscript.sh/
