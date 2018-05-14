import java.io.*;
import java.util.*;

public class myMergeSort{
 static Scanner scan=new Scanner(System.in);
 static int buffSize=400;
 
	public static String[] mergeSort(String[] myArray) {
	    String [] combinedArray = new String[myArray.length];
	    String[] leftHalf,rightHalf;
	    int first=0,last=0,z=0;
	    int splitValue;
	       if (myArray.length == 1) {
	    	   combinedArray = myArray;
	    } else {
	        if(myArray.length%2==0)
	        {
	        last=myArray.length; 
	        splitValue=(first+last)/2;
	        rightHalf = new String[splitValue];
	        }
	        else
	        {
	        last=myArray.length-1;
	        splitValue=(first+last)/2;
	        rightHalf = new String[splitValue+1];//+1
	        }     
	        leftHalf = new String[splitValue];
	        for (int x=0 ; x < splitValue; x++) {
	        	leftHalf[x] = myArray[x];
	        }
	        for (int y=splitValue; y < myArray.length; y++) {
	        	rightHalf[z] = myArray[y];
	            z++;
	        }
	        leftHalf = mergeSort(leftHalf);
	        rightHalf = mergeSort(rightHalf);
	        combinedArray = mergingData(leftHalf,rightHalf,myArray);
	   }

	    return combinedArray;
	}


	static String[] mergingData(String arrLeft[],String arrRight[],String myArray[])
	{
	    String[] joinedArray = new String[myArray.length];
	    int indexLeft = 0,indexRight=0,indexMiddle=0,indexComaparator=0;
	    while (indexLeft < arrLeft.length || indexRight < arrRight.length) {
	        if (indexLeft == arrLeft.length) {
	        	joinedArray[indexMiddle++] = arrRight[indexRight++];
	        } else if (indexRight == arrRight.length) {
	        	joinedArray[indexMiddle++] = arrLeft[indexLeft++];
	        } else {  
	        	indexComaparator = arrLeft[indexLeft].compareTo(arrRight[indexRight]);
	            if (indexComaparator > 0) {
	            	joinedArray[indexMiddle++] = arrRight[indexRight++];
	            } else if (indexComaparator < 0) {
	            	joinedArray[indexMiddle++] = arrLeft[indexLeft++];
	            } else { 
	            	joinedArray[indexMiddle++] = arrLeft[indexLeft++];
	            }
	        }   
	    }
	    return joinedArray;
	}
	
	static void mergingInidividualArrays(bufferStorageIndex arr[],int fileCount) throws IOException
	{

		String[] bufferArray=null;
		int count=0;
		for(int i=0;i<fileCount;i++)
		{
		arr[i]=new bufferStorageIndex(buffSize);
				count++;		
		}
		BufferedReader br[] = new BufferedReader[buffSize];
		for(int j=0;j<fileCount;j++)
		{
		String path="/tmp/Sorted"+j+".txt";
		scan=new Scanner(path);		
		br[j] = new BufferedReader(new FileReader(path));
		for(int k=0;k<arr[j].getLength();k++)
		{			
			arr[j].myArray[k]=br[j].readLine();
		}
		}
		
		comparingElements(arr,fileCount, br);
      		
	}
		static void comparingElements(bufferStorageIndex arr[],int fileCount, BufferedReader[] br) throws IOException
		{
			int mainLength=arr.length;
			int subLength=arr[0].getLength();
			String[] mergedArray=new String[mainLength];			
			PriorityQueue<elementInfoRecorder> pr=new PriorityQueue<elementInfoRecorder>();
				for(int i=0;i<5;i++)
			{
				pr.add(new elementInfoRecorder(arr[i].getMyArray()[0],i));
				arr[i].index++;
			}
			int i=0;
			FileWriter fileWrite=new FileWriter("/tmp/FinalSorted.txt",true);
			while(!pr.isEmpty()) {	
				elementInfoRecorder min= pr.remove();
				String finalElement=min.getName();
				mergedArray[i]=finalElement;
				i++;
				if(i == mergedArray.length) {
					for(int k=0;k<mergedArray.length;k++)
					 {
					fileWrite.write(mergedArray[k]+"\r\n");	
					 }					 
						
					 i = 0;
				}
				if(arr[min.arrayNumber].index == arr[min.arrayNumber].getLength()-1) {
					arr[min.arrayNumber].index=-1;
					for(int b=0;b<mergedArray.length;b++)	
					{
						arr[min.arrayNumber].myArray[b]=br[min.arrayNumber].readLine();	
						
					}	
					if(arr[min.arrayNumber].myArray[0]!=null) {
					pr.add(new elementInfoRecorder(arr[min.arrayNumber].getMyArray()[0],min.arrayNumber));			
					arr[min.arrayNumber].index++;
					}
				}
				else {
					pr.add(new elementInfoRecorder(arr[min.arrayNumber].myArray[arr[min.arrayNumber].index+1],min.arrayNumber));
					arr[min.arrayNumber].index++;
				}
			}
			 fileWrite.close();	
		}

	}


	

