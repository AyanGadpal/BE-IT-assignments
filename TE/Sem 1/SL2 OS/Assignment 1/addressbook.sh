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
    printf "\n=======================================================\n"
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

    printf "\n Record Added Successfully "
    unset zip
    unset name
    unset phone
    unset street
    unset state
    unset city
    unset no_
}

SearchRecord() {
    line
    echo "Entern Search Key"
    read key
    grep -r -w $key "temp"
    result=$(grep -r -w $key "temp")
    if [ -n "$result" ]; then
        echo "Found"
    else
        echo "Not Found"
    fi
}

DeleteRecord() {
    echo "Enter Name of you want"
    read pattern
    sed -i "/$pattern/d" $filename
}

ModifyRecord() {
    echo "Enter the Details of Person"
    read pattern
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
    sed -i "/$pattern/c\ $name $phone $no_ $street $state $city $zip" $filename
}

DisplayFile() {
    echo "FILE NAME : $filename\n"
    cat $filename
}

sorting() {
    line
    echo "Sort by ?"
    echo "1) Name"
    echo "2) Phone"
    echo "3) Building no."
    echo "4) Street"
    echo "5) State"
    echo "6) City"
    echo "7) Zip"
    echo "Your Choice : "
    read pattern
    line

    case $pattern in

    1) sort -s -k1 $filename ;;

    2) sort -s -k2 $filename ;;

    3) sort -s -k3 $filename ;;

    4) sort -s -k4 $filename ;;

    5) sort -s -k5 $filename ;;

    6) sort -s -k6 $filename ;;

    7) sort -s -k7 $filename ;;
    # Inproper Option Handling
    *) echo "ERROR :: Please Enter the Proper Option for 1 to 7." ;;
    esac
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
