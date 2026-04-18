import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Post extends HttpServlet {

    protected void doPost(HttpServletRequest request,
                          HttpServletResponse response)
            throws IOException {

        response.setContentType("text/html");
        PrintWriter pw = response.getWriter();

        Enumeration<String> e = request.getParameterNames();

        while (e.hasMoreElements()) {
            String pname = e.nextElement();
            String pvalue = request.getParameter(pname);
            pw.println(pname + " : " + pvalue + "<br>");
        }
    }
}
