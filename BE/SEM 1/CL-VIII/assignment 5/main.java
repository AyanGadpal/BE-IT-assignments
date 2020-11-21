import java.sql.Timestamp;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Vector;


// Super class User (Base class of Volunteer, Consumer and Admin)
class User {
    // Name and Email
    private String name, email;

    // Initialize name and email to NULL
    User() {
        name = null;
        email = null;
    }

    // Methods to get Name and Email of user
    public String getName() {
        /* Get Name from user */
        return null;
    }

    public String getEmail() {
        /* Get Email from user */
        return null;
    }

    // Protected methods to set Name and Email provided by user
    protected void setName(String name) {
        /* Set Name of user */
    }

    protected void setEmail(String email) {
        /* Set email of user */
    }
}



class Consumer extends User {
    // Attributes of Consumer
    private int c_id, quantity;
    private String type_of_shelter, shelter_name, area;
    private boolean food, status;

    // Get ConsumerID
    public int getId() {
        return -1;
    }

    // Get all the details of consumer
    public String getDetails() {
        return null;
    }

    // Check whether food is delivered to consumer or not
    public boolean getDeliveryStatus() {
        return false;
    }
}

class Volunteer extends User {
    // Attributes of Consumer
    private int v_id, status;
    private String organization, why_to_join, area, duration;
    private boolean working_days;

    // Get VolunteerID
    public int getId() {
        return -1;
    }
    
    // Set Status
    public void setStatus(String status)
    {
        /* Set status of volunteer*/
    }

    
     // Get Status of volunteer
    public String getStatus()
    {
        /* Get status of volunteer*/
        return null;
    }
    
    // Reset Status of Volunteer
    private void resetStatus(String status) {
        /* Reset status of Volunteer */
    }

    // Get all the details of volunteer
    public String getDetails() {
        return null;
    }
}

// Used to handle and log the donations
class Donation {
    
    /*  
        name : name of user who 
        Area : Area of donor, usefull in food 
    */
    private String name, Area;
    private Boolean type;
    private int panNumber, amount;
    private Timestamp generate;
   
    Donation()
    {
        // Registering the time of donation
        Date date = new Date();
        long time = date.getTime();
        this.generate  = new Timestamp(time);
    }

    Donation(String name,String Area,int panNumber,int amount,Boolean type)
    {
        //validating pan number
        if (validaded(panNumber))
        {
            Date date = new Date();
            long time = date.getTime();
            this.generate  = new Timestamp(time);
            
            this.name = name;
            this.Area = Area;
            this.panNumber = panNumber;
            this.amount = amount;
            this.type = type;
        }
        else
        {
            // Error
        }
        
    }
    
    private Boolean validaded(int panNumber){return true;}
    private Boolean PaymentAPI() {
        return false;
    }
    //Method for donating fund
    public int DonateFund() {
        return 0;
    }
    //Method for donating food
    public int DonateFood() {
        return 0;
    }

}

class Report {
    protected Boolean type;
    private Timestamp generate;
    protected Date start_date, end_date;

    Report()
    {
        // Registering the time of Report generation
        Date date = new Date();
        long time = date.getTime();
        this.generate  = new Timestamp(time);
    }

    // Setter Methods
    public void setReportType(Boolean type) {
        this.type = type;
    }

    // Setter Method used for defining the start date and end date of the report
    public void setDuration(Date start_date, Date end_date) {
        this.start_date = start_date;
        this.end_date = end_date;
    }
}

class Volunteer_Report extends Report{
    private Vector<Volunteer> volunteer;
    //method for fetching data as per report type
    public void SingleQuries() {/* */};
    public void groupQuries() {/**/};
}

class Donation_Report extends Report{
    private Vector<Donation> donations ;
    //method for fetching data as per report type
    public void SingleQuries() {/* */};
    public void groupQuries() {/* */};
}

class Consumer_Report extends Report{
    private Vector<Consumer> consumer ;
    //method for fetching data as per report type
    public void SingleQuries() {/* */};
    public void groupQuries() {/* */};
}

class Admin extends User {
    private String password;

    /* Set Password */
    private void setPassword(String password) {
        // Return Nothing
    }

    /* Checks Password*/
    private boolean checkPassword() {
        return false;
    }

    /* Forget Password for ADMIN */
    public String forgetPassword() {
        return null;
    }

    /* Mapping of Volunteer and Consumer */
    public String mapping() {
        return null;
    }

    /* Get the report of Volunteer / Consumer / Donoe */
    public String getReport(String type) {
        return null;
    }
}

class Mapping{
    Vector<Volunteer> VolunteerGroup;
    Consumer consumer;
    Date transactionDate;
    private int status;

    public void setVolunteerGroup(Vector<Volunteer> v){
        /*Get volunteers by group*/
        
    }
    
}

class NGO_data 
{
    private double totalFund = 0;
    private double totalCookedFood = 0;
    private double totalRawFood = 0;

    public double getTotalFund() { return totalFund; }
    public double getTotalCookedFood()  {return totalCookedFood;}
    public double getTotalRawFund() {return totalRawFood;}

    public void incCookedFood(double am)
    {
        this.totalCookedFood += am;
    }
    public void incRawFood(double am)
    {
        this.totalRawFood += am;
    }
    public void incFund(double am)
    {
        this.totalFund += am;
    }

}


public class main {
    public static void main(String[] args) {

    }
}