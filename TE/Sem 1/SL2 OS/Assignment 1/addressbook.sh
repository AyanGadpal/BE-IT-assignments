#!/bin/sh

#====================================================
# Auther     : Ayan N Gadpal 33308
# Script     : Address Book Using Bash Shell Scripting
# Date       : Jun 28 2019 / 10 am
# Copy Right : GNU public Library
#====================================================

# Run with -> $ bash addressbook.sh
# Note : Do not use ./ to run

# Output Formatting Line
line() {
    echo "======================================================="
}
sline() {
    echo "------------------------------------------------"
}

# FILE FUNCTIONS

AddRecord() {
    # Required to check the type of value in variable
    re='^[0-9]+$'
    # Taking Input from User for new Entry
    echo "Enter the Details of Person"
    while [ -z $name ]; do
        echo "Name "
        read name
    done
    sline
    while [ -z $phone ]; do
        echo "Phone"
        read phone
        if [ ${#phone} -ne 10 ] || ! [[ $phone =~ $re ]]; then
            echo "Not a valid number"
            unset phone
        fi
    done
    sline
    while [ -z $no_ ]; do
        echo "Building / flat / house No "
        read no_
        if ! [[ $no_ =~ $re ]]; then
            echo "Not a valid number"
            unset no_
        fi

    done
    sline
    while [ -z $street ]; do
        echo "Street "
        read street
    done
    sline
    while [ -z $state ]; do
        echo "State "
        read state
    done
    sline
    while [ -z $city ]; do
        echo "City "
        read city
    done
    sline
    while [ -z $zip ]; do
        echo "Zip"
        read zip
        if [ ${#zip} -ne 6 ] || ! [[ $zip =~ $re ]]; then
            echo "Not a valid number"
            unset zip
        fi
    done
    sline

    # Adding Record
    printf "\n%10s %10s %5s %8s %14s %10s %6s" $name $phone $no_ $street $state $city $zip >>"$filename"
    
    echo "\n Record Added Successfully "
}

SearchRecord() {
    echo "Enter The Name Or Roll No of Student You Want to Search"
    read pattern
    grep -r -w $pattern $filename
    result=$(grep -r -w $pattern $filename)
    if [ -n "$result" ]; then
        echo "Found"
    else
        echo "Not Found"
    fi
}

DeleteRecord() {
    echo "Enter the Roll or Name No you want to be removed"
    read pattern
    sed -i "/$pattern/d" $filename
}

ModifyRecord() {
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

DisplayFile() {

    echo "FILE NAME : $filename\n"
    cat $filename
}

sorting() {
    sort -k 20n $filename
}

# MAIN

# MENU
filename="addressbook.txt"
touch $filename
while :; do
    line
    echo "Address Book"
    echo "1) Display Address Book"
    echo "2) Add Record"
    echo "3) Search"
    echo "4) Delete"
    echo "5) Modify"
    echo "6) Sort"
    echo "7) Exit"
    echo "Your Choice : "
    read Choice
    line

    case $Choice in

    # Display the File
    1) DisplayFile ;;

    # Enter the Records
    2)
        echo "Enter the number of records to be inserted : "
        read num
        while [ $num -ne 0 ]; do
            num=$(expr $num - 1)
            AddRecord
            line
        done
        ;;

    # Search Some Record Within The File
    3) SearchRecord ;;

    # Delete Some Record from the File
    4) DeleteRecord ;;

    # Modify the Record of the File
    5) ModifyRecord ;;

    # Sort
    6) sorting ;;

    # Exit
    7) exit ;;

    # Inproper Option Handling
    *) echo "ERROR :: Please Enter the Proper Option for 1 to 7." ;;
    esac
done
line
