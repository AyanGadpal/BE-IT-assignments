

import java.io.IOException;
import java.io.Writer;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class DemoClass2
 */
@WebServlet("/DemoClass2")
public class DemoClass2 extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public DemoClass2() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		//response.getWriter().append("Served at: ").append(request.getContextPath());
		response.setContentType("text/html");
		
		PrintWriter out = response.getWriter();
		out.print("<html><body>");
		
		out.print("<h1>Hello World</h1>");
		
		out.print("</html></body>");
		
	
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		
		// Take Username from input field
		String un = request.getParameter("username");
		
		// Take Password from input field
		String pw = request.getParameter("password");
		response.setContentType("text/html");
		
		// Take Writer
		PrintWriter out = response.getWriter();
		
		out.print("<html><body>");
		
		if(un.equals("Admin") && pw.equals("Admin"))
		{
			out.print("<h1>Login Successfull</h1>");
		}
		if(!un.equals("Admin") || !pw.equals("Admin"))
		{
			out.print("<h1>Login failed</h1>");
		}
		out.print("</html></body>");
		
	}

}
