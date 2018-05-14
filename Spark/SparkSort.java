import org.apache.spark.SparkConf;

import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.JavaSparkContext;
import org.apache.spark.api.java.function.Function;
import org.apache.spark.api.java.*;
import java.util.Arrays;
 
public class SparkSort {
	public static void main(String[] args) {

		SparkConf conf = new SparkConf().setAppName("SparkSort").setMaster("yarn");
		JavaSparkContext js = new JavaSparkContext(conf);
		JavaRDD<String> tf = js.textFile(args[0]);
		JavaRDD<String> ta=tf.flatMap(s->Arrays.asList(s).iterator());
                JavaRDD<String> tfs = ta.sortBy(new Function<String, String>() {
			public String call(String n1) throws Exception {
				return n1.substring(0, 10);
			}
		},true,4);
		tfs.flatMap(s->Arrays.asList(s+="\r").iterator()).saveAsTextFile(args[1]);
	}
}
