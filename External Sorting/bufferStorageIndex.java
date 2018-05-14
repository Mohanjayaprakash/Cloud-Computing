
public class bufferStorageIndex {

	String[] myArray;
	int index;
	
	public bufferStorageIndex(int size)
	{		
		myArray=new String[size];
	    index=-1;
	}
	
	bufferStorageIndex()
	{}
	
	public int getLength() {
		return myArray.length;
	}
	
	public String[] getMyArray() {
		return myArray;
	}

	public void setMyArray(String[] myArray) {
		this.myArray = myArray;
	}

	public int getIndex() {
		return index;
	}

	public void setIndex(int index) {
		this.index = index;
	}
	
	
}
