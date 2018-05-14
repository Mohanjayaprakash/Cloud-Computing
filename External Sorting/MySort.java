import java.io.*;
import java.util.*;

public class MySort{
	
	static Scanner scan=new Scanner(System.in);
	static int lineNumber=0;
    static int buffSize=400;
    
    public static void main(String[] args) throws IOException, InterruptedException {
    myMergeSort myms=new myMergeSort();
	String path=args[0];
 	int totalLines = 0,dividedInput=0,countLoopTimes=0;;
	totalLines =(int) lineCount(path);
	bufferStorageIndex[] mergingArray;
	System.out.println("Total Number of Lines:"+totalLines);
	if(totalLines==20000000)
	{
		dividedInput=20000000/5;
		mergingArray=new bufferStorageIndex[buffSize];
	}
	else if(totalLines==200000000)
	{
		dividedInput=200000000/20;
		mergingArray=new bufferStorageIndex[buffSize];
	}
	else
	{
		dividedInput=2000/5;
		mergingArray=new bufferStorageIndex[buffSize];
	}
	BufferedReader br = new BufferedReader(new FileReader(path));
	for(int k=0;k<totalLines;k+=dividedInput)
	{
	String[] myArray=new String[dividedInput];
 	readfile(br,myArray,lineNumber);
  	String[] finalList=myms.mergeSort(myArray);
	fileWrite(finalList,countLoopTimes);
	countLoopTimes++;	
	}
	myms.mergingInidividualArrays(mergingArray,countLoopTimes);
}

public static void readfile(BufferedReader br, String[] arr,int lineNumber) throws IOException                     
{
  
	for(int i=0;i<arr.length;i++)
	{	 
	arr[i]=br.readLine();
	}
}


public static void fileWrite(String[] source,int countTimes) throws IOException
{
	FileWriter fileWrite=new FileWriter("/tmp/Sorted"+countTimes+".txt");
	{
	 for(int i=0;i<source.length;i++)
	 {
	fileWrite.write(source[i]+"\r\n");
	 }
	 fileWrite.close();
}
}

public static long lineCount(String path) throws IOException
{
	BufferedReader read = new BufferedReader(new FileReader(path));
    int count = 0;
    String line;
    while ((line = read.readLine()) != null)
    {
        count++;
    }
    read.close();
    return count;
 }
}
