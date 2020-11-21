import java.sql.Timestamp;
import java.text.SimpleDateFormat;
import java.util.Date;


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
    
    public void SingleQuries() {};
    public void groupQuries() {};
}

class Donation_Report extends Report{
    private Vector<Donations> Donations ;

    public void SingleQuries() {};
    public void groupQuries() {};
}

class Consumer_Report extends Report{
    private Vector<Consumer> consumer ;

    public void SingleQuries() {};
    public void groupQuries() {};
}
