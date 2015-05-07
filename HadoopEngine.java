

import java.util.*; 

import java.io.IOException; 

import org.apache.hadoop.fs.Path; 
import org.apache.hadoop.io.*; 
import org.apache.hadoop.mapred.*; 

public class HadoopEngine 
{ 
   //Mapper class 
   public static class EngineMapper extends MapReduceBase implements 
   Mapper<LongWritable ,/*Input key Type */ 
   Text,                /*Input value Type*/ 
   Text,                /*Output key Type*/ 
   FloatWritable>        /*Output value Type*/ 
   { 
      
      //Map function 
      public void map(LongWritable key, Text value, 
      OutputCollector<Text, FloatWritable> output,   
      Reporter reporter) throws IOException 
      { 
         String line = value.toString(); 
         String lasttoken = null; 
         StringTokenizer s = new StringTokenizer(line,","); 
         String date = s.nextToken(); 
         
         while(s.hasMoreTokens())
            {
               lasttoken=s.nextToken();
            } 
         float rate = Float.parseFloat(lasttoken); 
         output.collect(new Text(date), new FloatWritable(rate)); 
      } 
   } 
   
   
   //Reducer class 
   public static class EngineReduce extends MapReduceBase implements 
   Reducer< Text, FloatWritable, Text, FloatWritable > 
   {  
   
      //Reduce function 
      public void reduce( Text key, Iterator <FloatWritable> values, 
         OutputCollector<Text, FloatWritable> output, Reporter reporter) throws IOException 
         { 
           float sum=0;
           int size=0;
           float avg=0;
            
            while (values.hasNext()) 
            { 
            	sum+=values.next().get();
            	size++;
            } 
            avg=sum/size;
            output.collect(key, new FloatWritable(avg));
         } 
   }  
   
   
   //Main function 
   public static void main(String args[])throws Exception 
   { 
      JobConf conf = new JobConf(HadoopEngine.class); 
      
      conf.setJobName("max_eletricityunits"); 
      conf.setOutputKeyClass(Text.class);
      conf.setOutputValueClass(FloatWritable.class); 
      conf.setMapperClass(EngineMapper.class); 
      conf.setCombinerClass(EngineReduce.class); 
      conf.setReducerClass(EngineReduce.class); 
      conf.setInputFormat(TextInputFormat.class); 
      conf.setOutputFormat(TextOutputFormat.class); 
      
      FileInputFormat.setInputPaths(conf, new Path(args[0])); 
      FileOutputFormat.setOutputPath(conf, new Path(args[1])); 
      
      JobClient.runJob(conf); 
   } 
} 