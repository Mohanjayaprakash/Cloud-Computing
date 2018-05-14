import java.io.IOException;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import static org.junit.Assert.*;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.NullWritable;

public class HadoopSort
  {
	public static class mapperFunction extends Mapper<Object, Text, Text, Text>
        {
		public void map (Object keyValue, Text text, Context info)throws IOException, InterruptedException
                {
	    	        String key1 = (text.toString()).substring(0,10);
			String key2  = (text.toString()).substring(10);
			info.write(new Text(key1),new Text(key2));
		}
	}
	public static class reducerFunction extends Reducer<Text, Text, Text, Text>
       {		
		public void reduce (Text text1, Iterable<Text> value, Context info)throws IOException, InterruptedException
                {
			      for (Text text : value) 
                {
				info.write(new Text(text1), text);
		}
	}}
	
	public static void main(String[] args) throws Exception
             {		
                Configuration setup = new Configuration();
		Job work = Job.getInstance(setup, "Hadoop Sorting");
                Path p1=new Path(args[0]);
                Path p2=new Path(args[1]);
		work.setJarByClass(HadoopSort.class);
		work.setMapperClass(mapperFunction.class);
		work.setCombinerClass(reducerFunction.class);
		work.setReducerClass(reducerFunction.class);
		work.setOutputKeyClass(Text.class);
		work.setOutputValueClass(Text.class);
		FileInputFormat.addInputPath(work,p1);
		FileOutputFormat.setOutputPath(work,p2);
		work.waitForCompletion(true);
                assertTrue("Job Not failed", !work.isSuccessful());
	}
     }

