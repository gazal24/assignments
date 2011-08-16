/*
  Gazal Garg
  08CS3012
  Assignment 1.3
*/

import java.io.* ;
import java.sql.* ;
import java.util.* ;

public class ConfigureDB 
{
    public static Connection con ;
    public static Statement stmt ;
    /*String table_name ="";	
      static String[] init_db = {
      //place your queries here as string.
      };	*/

    public ConfigureDB ()
    {
	System.out.println("TEST : HELLO");    
	con = null;
	stmt = null;
			
	String sDriver = "oracle.jdbc.driver.OracleDriver";
	String sURL = "jdbc:oracle:thin:@10.5.18.45:1521:xe";
	String sUsername = "dbms013";
	String sPassword = "82ab0777";

	try    
	    {     
       	 	Class.forName( sDriver ).newInstance();
		System.out.println("Driver Load Success") ;
	    }
	catch( Exception e )  
	    {     		
      		System.exit(0);
	    } 

	try
	    {
      		con = DriverManager.getConnection( sURL, sUsername ,sPassword);
		stmt = con.createStatement();     				
		System.out.println("\n\n>>QUERY 1 :\n========== \nSTUDENT NAMES\n");
		query1(con);
		System.out.println("\n\n>>QUERY 2 :\n========== \nSSN NO. \t STUDENT NAME\n");
		query2(con);
		System.out.println("\n\n>>QUERY 3 :\n========== \nSTUDENT NAME\n");
		query3(con);  				
		System.out.println("\n\n>>QUERY 4 :\n========== \nSTUDENT NAME\n");
		query4(con);
		System.out.println("\n\n>>QUERY 5 :\n========== \nCOURSE \t\t DEPARTMENT \t\t\t GRADE\n");
		query5(con);
	    }
	catch ( Exception e)
	    {     		 
		System.err.println( e.getMessage() );     		 
	    }
    }
	
		
    public static void query1(Connection con)
    {

	Statement stmt;

	try{
	    stmt=con.createStatement();
	    ResultSet result= stmt.executeQuery(
						"SELECT Students.Name as NAME FROM Students, Grades, Courses, Sections WHERE Grades.Student=Students.SSN AND Grades.Section = Sections.SectionNum AND Courses.code = Sections.Course GROUP BY Students.Name HAVING COUNT(DISTINCT Courses.Deparment)>1");


	    while(result.next())
                {
                    System.out.println(result.getString("NAME")+"\t");
                }
	    result.close();
	}
	catch(Exception e)
            {
		System.err.println( e.getMessage() );
            }

    }		

	
    public static void query2(Connection con)
    {
	Statement stmt;
	try{
	    stmt=con.createStatement();
	    ResultSet result=stmt.executeQuery("SELECT Students.Name AS NAME, Students.SSN AS SSN FROM Grades, Sections, Courses, Students WHERE Students.SSN = Grades.Student AND Grades.Section = Sections.SectionNum AND Courses.Code = Sections.Course GROUP BY Students.Name, Students.SSN HAVING COUNT (*)>1");

	    while(result.next())
                {
		    System.out.println(result.getString("SSN")+"\t"+result.getString("NAME"));
                }
	    result.close();
	}
	catch(Exception e)
            {
                System.err.println(e.getMessage());
            }
    }

    public static void query3(Connection con)
    {
	Statement stmt;
	try{
	    stmt=con.createStatement();

	    ResultSet result=stmt.executeQuery(
					       "select students.name from students where students.ssn in (select students.ssn from students, grades where students.ssn = grades.student group by students.ssn having 'b' >=  all(select grade from grades, students where grades.student=students.ssn))"
					       );
	    while(result.next())
		{
		    System.out.println(result.getString("NAME"));
		}
	    result.close();
	}
	catch(Exception e)
            {
                System.err.println(e.getMessage());
            }
    }


    public static void query4(Connection con)
    {
	Statement stmt;
	try{
	    stmt=con.createStatement();

	    ResultSet result=stmt.executeQuery(
					       "SELECT DISTINCT STUDENTS.NAME FROM STUDENTS,GRADES WHERE STUDENTS.SSN=GRADES.STUDENT  AND GRADES.DEPARTMENT = 'CS' AND STUDENTS.SSN NOT IN ( SELECT STUDENTS.SSN FROM STUDENTS, GRADES WHERE STUDENTS.SSN = GRADES.STUDENT AND GRADES.DEPARTMENT = 'CS'  AND (GRADE='B' OR GRADE ='C' OR GRADE ='D') )"
					       );
	    
	    while(result.next())
		{
		    System.out.println(result.getString("NAME"));
		}
	    result.close();
	}
	catch(Exception e)
            {
                System.err.println(e.getMessage());
            }
    }

    public static void query5(Connection con)
    {
	Statement stmt;
	try{
	    stmt=con.createStatement();

	    ResultSet result=stmt.executeQuery(
					       "SELECT GRADES.COURSE, STUDENTS.DEPARTMENT, MIN(GRADES.GRADE) AS GRADE FROM GRADES, STUDENTS WHERE STUDENTS.SSN = GRADES.STUDENT GROUP BY GRADES.COURSE, STUDENTS.DEPARTMENT"
					       );

	    while(result.next())
		{
		    System.out.println(result.getString("COURSE")+"\t\t\t"+result.getString("DEPARTMENT")+"\t\t\t"+result.getString("GRADE"));
		}
	    result.close();
	}
	catch(Exception e)
            {
                System.err.println(e.getMessage());
            }
    }

    public static void main(String args[])
    {
	ConfigureDB db= new ConfigureDB();
	return;
    }
}

