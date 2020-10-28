import java.util.Scanner;
import java.math.BigInteger; 
import java.security.MessageDigest; 
import java.security.NoSuchAlgorithmException; 

public class sha { 
	public static String encryptSHA(String input) 
	{ 
		try { 
            MessageDigest md = MessageDigest.getInstance("SHA-1"); 
            
			// to calculate message digest of the input string 
			byte[] messageDigest = md.digest(input.getBytes()); 

			// Convert byte array into signum representation 
			BigInteger no = new BigInteger(1, messageDigest); 

			// Convert message digest into hex value 
			String ht= no.toString(16); 

			// Add preceding 0s to make it 32 bit 
			while (ht.length() < 32) { 
				ht = "0" + ht; 
			} 

			// return the HashText 
			return ht; 
		} 

		// For specifying wrong message digest algorithms 
		catch (NoSuchAlgorithmException e) { 
			throw new RuntimeException(e); 
		} 
	} 

	public static void main(String args[]) throws NoSuchAlgorithmException 
	{ 
		String s1, s2;
		Scanner sc = new Scanner(System.in); 
		
		System.out.print("1) String :");
		s1 = sc.nextLine();
		System.out.println();
		System.out.println("\n" + s1 + " : " + encryptSHA(s1)); 
		
		System.out.print("2) String :");
		s2 = sc.nextLine();
		System.out.println();
		System.out.println("\n" + s2 + " : " + encryptSHA(s2)); 
	} 
}