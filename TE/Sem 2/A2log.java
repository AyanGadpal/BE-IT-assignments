package logCounter;

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;

import org.apache.hadoop.fs.Path;

import org.apache.hadoop.io.IntWritable;

import org.apache.hadoop.io.LongWritable;

import org.apache.hadoop.io.Text;

import org.apache.hadoop.mapreduce.Job;

import org.apache.hadoop.mapreduce.Mapper;

import org.apache.hadoop.mapreduce.Reducer;

import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;

import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

import org.apache.hadoop.util.GenericOptionsParser;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class logCounter {

	// Main
	public static void main(String[] args) throws Exception

	{

		Configuration c = new Configuration();

		String[] files = new GenericOptionsParser(c, args).getRemainingArgs();

		Path input = new Path(files[0]);

		Path output = new Path(files[1]);

		Job j = new Job(c, "logCounter");

		j.setJarByClass(logCounter.class);

		j.setMapperClass(MapForLogCount.class);

		j.setReducerClass(ReduceForLogCount.class);

		j.setOutputKeyClass(Text.class);

		j.setOutputValueClass(IntWritable.class);

		FileInputFormat.addInputPath(j, input);

		FileOutputFormat.setOutputPath(j, output);

		System.exit(j.waitForCompletion(true) ? 0 : 1);

	}

	public static class MapForLogCount extends Mapper<LongWritable, Text, Text, IntWritable> {

		public void map(LongWritable key, Text value, Context con) throws IOException, InterruptedException

		{

			String line = value.toString();

			String[] words = line.split(",");

			String Ip = words[1];
			String[] StartyearTime = words[5].split(" ");
			String year = StartyearTime[0];

			// Getting the start time
			String Starttime = StartyearTime[1];

			String[] EndyearTime = words[7].split(" ");
			String endtime = EndyearTime[1];

			SimpleDateFormat format = new SimpleDateFormat("HH:mm:ss");
			Date date1 = null;
			try {
				date1 = format.parse(Starttime);
			} catch (ParseException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			Date date2 = null;
			try {
				date2 = format.parse(endtime);
			} catch (ParseException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

			long difference = date2.getTime() - date1.getTime();

			String IpYear = Ip + "\t" + year;

			Text outputKey = new Text(IpYear);

			IntWritable outputValue = new IntWritable((int) difference);

			con.write(outputKey, outputValue);

		}

	}

	public static class ReduceForLogCount extends Reducer<Text, IntWritable, Text, IntWritable>

	{

		public void reduce(Text word, Iterable<IntWritable> values, Context con)
				throws IOException, InterruptedException

		{

			int sum = 0;

			for (IntWritable value : values)

			{

				sum += value.get();

			}

			con.write(word, new IntWritable(sum));

		}

	}

}
