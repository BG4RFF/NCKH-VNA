package com.example.manht.testbluetooth;

import android.content.Intent;
import android.graphics.Color;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.github.mikephil.charting.charts.LineChart;
import com.github.mikephil.charting.components.AxisBase;
import com.github.mikephil.charting.components.XAxis;
import com.github.mikephil.charting.components.YAxis;
import com.github.mikephil.charting.data.Entry;
import com.github.mikephil.charting.data.LineData;
import com.github.mikephil.charting.data.LineDataSet;
import com.github.mikephil.charting.formatter.IAxisValueFormatter;
import com.github.mikephil.charting.highlight.Highlight;
import com.github.mikephil.charting.interfaces.datasets.ILineDataSet;
import com.github.mikephil.charting.listener.OnChartValueSelectedListener;

import java.util.ArrayList;
import java.util.List;

public class DisplayDiagram extends AppCompatActivity {
    String address;
    double[] frequencies, magnitude;

    LineChart chart;
    TextView txtShowFrequencyInfo, txtShowMagnitudeInfo, txtShowQualityInfo;

    List<String> labels;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Intent newIntent = getIntent();
        address = newIntent.getStringExtra(DeviceList.EXTRA_ADDRESS);
        frequencies = newIntent.getDoubleArrayExtra(SetFrequencyActivity.EXTRA_FREQUENCY);
        magnitude = newIntent.getDoubleArrayExtra(SetFrequencyActivity.EXTRA_MAGNITUDE_RESULT);

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_display_diagram);

        txtShowFrequencyInfo = (TextView) findViewById(R.id.txtShowFrequencyInfo);
        txtShowMagnitudeInfo = (TextView) findViewById(R.id.txtShowMagnitudeInfo);
        txtShowQualityInfo = (TextView) findViewById(R.id.txtShowQualityInfo);

        chart = (LineChart) findViewById(R.id.chart);
        chart.getDescription().setEnabled(false);
        chart.setPinchZoom(true);
        chart.getAxisRight().setEnabled(false);
        chart.setOnChartValueSelectedListener(new OnChartValueSelectedListener() {
            @Override
            public void onValueSelected(Entry e, Highlight h) {
                txtShowFrequencyInfo.setText(labels.get((int) e.getX()) + " MHz");
                txtShowMagnitudeInfo.setText(String.valueOf(e.getY()) + " dB");
//                txtShowQualityInfo
            }

            @Override
            public void onNothingSelected() {
                txtShowFrequencyInfo.setText("Not selected");
                txtShowMagnitudeInfo.setText("Not selected");
                txtShowQualityInfo.setText("Not selected");
            }
        });

        List<String> labels = new ArrayList<>();
        for (double d : frequencies) {
            labels.add(String.valueOf(d));
        }

        List<Float> ds1 = new ArrayList<>();
        for (double d : magnitude) {
            ds1.add((float) d);
        }

        setData(labels, ds1);
    }

    private void setData(List<String> Labels, List<Float> DataSet1) {
        List<ILineDataSet> dataSets = new ArrayList<ILineDataSet>();

        List<Entry> entries1 = new ArrayList<Entry>();
        for (int i = 0; i < DataSet1.size(); i++) {
            entries1.add(new Entry(i, DataSet1.get(i)));
        }
        LineDataSet dataSet1 = new LineDataSet(entries1, "Magnitude");
        dataSet1.setColor(Color.rgb(0, 0, 230));
        dataSets.add(dataSet1);

        labels = Labels;
        IAxisValueFormatter axisValueFormatter = new IAxisValueFormatter() {
            @Override
            public String getFormattedValue(float value, AxisBase axis) {
                if (value < labels.size()) {
                    return labels.get((int) value);
                } else {
                    return "Undefined";
                }
            }
        };
        XAxis xAxis = chart.getXAxis();
        xAxis.setGranularity(1f);
        xAxis.setPosition(XAxis.XAxisPosition.BOTTOM);
        xAxis.setDrawAxisLine(false);
        xAxis.setDrawGridLines(false);
        xAxis.setValueFormatter(axisValueFormatter);

        LineData lineData = new LineData(dataSets);
        chart.setData(lineData);
    }
}
