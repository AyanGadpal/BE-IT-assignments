# Auther : Ayan N Gadpal
# Code : Address Book
# Record Format : ( name,phone,building no,street,state,city,zip )

# Note : For Simplicity 
# Record Format : ( name,phone,zip )


# For Output Formatting
line(){
        printf "\n\n======================================\n"
}


# 1) Display START
Display(){
       cat $filename
}
# Display END

# 2) Add Record START
AddRecord(){

        # Reguler Expression for Recognizing Number
        re='^[0-9]+$'
        
        echo "Enter The Details of the person"

        # Keep Asking for Name untill valid name is accepted
        while [ -z $name ]; do
                echo "Name"
                read name
        done

        # Keep Asking for Phone no. untill valid Phone no. is accepted
        while [ -z $phone ]; do
                echo "Phone"
                read phone
                # Check if number is 10 digit AND contain only numbers
                if [ ${#phone} -ne 10 ] || ! [[ $phone =~ $re ]]; then
                        echo "Not a valid number"
                        unset phone
                fi
        done
        
        # Keep Asking for Phone no. untill valid Phone no. is accepted
        while [ -z $zipno ]; do
                echo "Zip"
                read zipno
                # Check if number is 6 digit AND contain only numbers
                if [ ${#zipno} -ne 6 ] || ! [[ $phone =~ $re ]]; then
                        echo "Please Enter a Valid Zip Code"
                        unset zipno
                fi
        done
        
        # Finally enter the valid data into file
        printf "\n%10s %10s %10s" $name $phone $zipno >> "$filename"
       
        unset name
        unset phone
        unset zipno
        
}
# Add Record END

# 3) Search START
Search(){
   
   # Ask for key such as name ,phone or zip
   echo "Enter the key"
   read key
   
   # -r Recursive Search, -w for Word Based Search
   # && means if found 
   # || means else
   (grep -r -w $key $filename && echo "Found !") || echo "Not Found !"

}
# Search END


# 4) Delete START
Delete(){
        # Ask for the key whose record is to be removed
        echo "Enter the Key"
        read key
         
        # i) Search the record to be Deleted
        # ii) Remove it if Found
        if grep -r -w $key $filename; then
                # If Record is found
                sed -i "/$key/d" $filename 
                echo "Record Deleted Successfull !"
        else
                # If Record is not found
                echo "Record Not Found !"            
        fi 
}
# Delete END


# 5) Modify START
Modify(){
        echo "Enter the Key"
        read key
        
        while [ -z $name ]; do
                echo "Name"
                read name
        done

        # Keep Asking for Phone no. untill valid Phone no. is accepted
        while [ -z $phone ]; do
                echo "Phone"
                read phone
                # Check if number is 10 digit AND contain only numbers
                if [ ${#phone} -ne 10 ] || ! [[ $phone =~ $re ]]; then
                        echo "Not a valid number"
                        unset phone
                fi
        done
        
        # Keep Asking for Phone no. untill valid Phone no. is accepted
        while [ -z $zipno ]; do
                echo "Zip"
                read zipno
                # Check if number is 6 digit AND contain only numbers
                if [ ${#zipno} -ne 6 ] || ! [[ $phone =~ $re ]]; then
                        echo "Please Enter a Valid Zip Code"
                        unset zipno
                fi
        done
        sed -i "/$key/c\ $name $phone $zipno" $filename
        
        unset name
        unset phone
        unset zipno
        
}

# Modify END


# 6) Sort START

# Sort END

# MAIN 
filename="addressbook.txt"
touch $filename

while :; do
       line
       echo "Address Book"
       echo "1) Display"
       echo "2) Add Record"
       echo "3) Search"
       echo "4) Delete"
       echo "5) Modify"
       echo "6) Sort"
       echo "7) Exit"
       read choice
       line
       case $choice in
       
       1) Display;;
       
       2) echo "How many records you want to enter ?"
          read no
          while [ $no -ne 0 ]; do
                AddRecord  
                no=$(expr $no - 1)     
          done
          ;;
       
       3) Search;;
       
       4) Delete;;
       
       5) Modify;;
       
       6) echo "6";;
       
       7) exit;;
       
       *) echo "Please choose correct option from 1 to 7 only"
       
       esac
       
done
