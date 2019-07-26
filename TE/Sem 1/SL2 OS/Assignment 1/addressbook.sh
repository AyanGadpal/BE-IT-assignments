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
    printf "\n=================================================================\n"
}
sline() {
    echo "---------------------------------------------------------------"
}

# FILE FUNCTIONS

# To Insert a single record into the address book
AddRecord() {
    # Required to check the type of value in variable
    re='^[0-9]+$'
    # Taking Input from User for new Entry
    echo "Enter the Details of Person"

    while [ -z $name ]; do # Do not allow Null
        echo "Name "
        read name
    done
    sline
    while [ -z $phone ]; do
        echo "Phone"
        read phone

        # Input Validation for 10 digit number
        if [ ${#phone} -ne 10 ] || ! [[ $phone =~ $re ]]; then
            echo "Not a valid number"
            unset phone # Unset the invalid phone number
        fi

        # Unique phone number validation
        if [ -n $phone ]; then

            (grep -r -w $phone $filename) && unset phone
            if [ -z $phone ]; then
                echo "ERROR : Phone number Already Present !"
            fi

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

        # Input Validation for 6 digit number
        if [ ${#zip} -ne 6 ] || ! [[ $zip =~ $re ]]; then
            echo "Not a valid number"
            unset zip
        fi
    done
    sline

    # Adding Record to the file
    printf "\n%10s %10s %9s %8s %14s %10s %6s" $name $phone $no_ $street $state $city $zip >>"$filename"

    printf "\nRecord Added Successfully "

    # Unsetting variables for Next Record
    unset zip
    unset name
    unset phone
    unset street
    unset state
    unset city
    unset no_
}

# Search an entry from the address book
SearchRecord() {
    line

    # Ask for key such as name,phone number
    echo "Entern Search Key"
    read key

    # Search for that key and print appropiate message
    (grep -r -w $key $filename && echo "Found") || echo "Not found"
}

# Delete an entry from the address book
DeleteRecord() {
    echo "Enter Name of you want"
    read pattern
    if grep -r -w $pattern $filename; then
        sed -i "/$pattern/d" $filename
        echo "Deletion Successful"
    else
        echo "Record Not Found !"
    fi
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

    # MODIFY THE RECORD
    sed -i "/$pattern/c\ $name $phone $no_ $street $state $city $zip" $filename
}

# DISPLAY THE CONTENT OF THE FILE
DisplayFile() {
    echo "FILE NAME : $filename\n"
    printf "\n      NAME      PHONE BUILDING STREET         STATE     CITY      ZIP\n"
    sline
    cat $filename
}

# DISPLAY THE CONTENT OF THE FILE WITH SORTING
sorting() {
    line

    # ASK USER FOR WHICH COLUNM THEY WANT
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

    1) sort -s -k1 $filename ;; # NAME WISE

    2) sort -s -k2 $filename ;; # PHONE WISE

    3) sort -s -k3 $filename ;; # BUILDING WISE

    4) sort -s -k4 $filename ;; # STREET WISE

    5) sort -s -k5 $filename ;; # STATE WISE

    6) sort -s -k6 $filename ;; # CITY WISE

    7) sort -s -k7 $filename ;; # ZIP WISE

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
