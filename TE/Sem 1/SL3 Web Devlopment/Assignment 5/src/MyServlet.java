import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/MyServlet")
public class MyServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
	String u = "abc";
	String p = "1234";

	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String uname = request.getParameter("username");
		String pwd = request.getParameter("password");
		//PrintWriter out = response.getWriter();
		try
		{
			if(uname.equals(u))
			{
				if(pwd.equals(p))
				{
					System.out.println("Success!..");
					response.sendRedirect("login.jsp");
				}
				else
					System.out.println("Password Error!");
			}
			else
			{
				System.out.println("Login Error!");
			}
		}
		catch(Exception e)
		{
			System.out.print("Exception :"+e);
		}
	}

}
