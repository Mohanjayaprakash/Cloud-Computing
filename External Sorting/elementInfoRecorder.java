
import java.util.Comparator;

public class elementInfoRecorder implements Comparator<elementInfoRecorder>,Comparable<elementInfoRecorder>{

	String name;
	int arrayNumber;
	
	public elementInfoRecorder(String names,int number)
	{
		this.name=names;
		this.arrayNumber=number;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getArrayNumber() {
		return arrayNumber;
	}

	public void setArrayNumber(int arrayNumber) {
		this.arrayNumber = arrayNumber;
	}

	@Override
	public int compare(elementInfoRecorder arg0, elementInfoRecorder arg1) {
		// TODO Auto-generated method stub
		//arg0.name.compareTo(arg1.name) < 0
		if (arg0.name.compareTo(arg1.name) < 0) {
			return -1;
		}
		else if (arg0.name.compareTo(arg1.name) > 0)
			return 1;
		else 
			return 0;
	}

	@Override
	public int compareTo(elementInfoRecorder arg1) {
		// TODO Auto-generated method stub
		if (this.name.compareTo(arg1.name) < 0) {
			return -1;
		}
		else if (this.name.compareTo(arg1.name) > 0)
			return 1;
		else 
			return 0;
	}
	
}
