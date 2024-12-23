# Usage Guide

## Getting Started

Launch the application to see the main window with:
- A coordinate system display
- Curve type selection buttons
- Curve smoothing checkbox

## Available Curve Types

### 1. Random Curve
- Click the "Random Curve" button
- Points are randomly generated across the coordinate system
- Each point's y-coordinate is randomly determined
- Points are evenly spaced along the x-axis
- Example usage:
```cpp
// Programmatically generate random curve
void MainWidget::on_randCurve_clicked(bool checked)
{
    if(checked) {
        // Generate random points
        randp.clear();
        int x = width()/-2;
        for(int i=1; i<=n; i++) {
            randp.append(QPointF(x, random_y_value));
            x += 50;
        }
    }
}
```

### 2. Sine Curve
- Click the "Sin Curve" button
- Displays a sinusoidal wave
- Points follow the mathematical sine function
- Demonstrates periodic wave patterns
- Example usage:
```cpp
// Generate sine wave points
points.append(QPointF(x, width()/4*sin((i-1)*PI/2)));
```

### 3. Logarithmic Curve
- Click the "Ln Curve" button
- Shows logarithmic growth pattern
- Points follow natural logarithm function
- Demonstrates logarithmic scaling
- Example usage:
```cpp
// Generate logarithmic curve points
points.append(QPointF(x, -1*log(x/50.0)*50));
```

### 4. Exponential Curve
- Click the "Ex Curve" button
- Displays exponential growth
- Points follow exponential function
- Shows rapid growth characteristics
- Example usage:
```cpp
// Generate exponential curve points
points.append(QPointF(x, -1*pow(2.732,(i*100-width()/2)/100.0)*50));
```

## Curve Smoothing

### Toggle Smoothing
1. Use the checkbox to enable/disable curve smoothing
2. When enabled:
   - Points are connected using Bezier curves
   - Smooth transitions between points
   - Demonstrates the Bezier curve algorithm
3. When disabled:
   - Points are connected with straight lines
   - Shows original point connections
   - Useful for comparing smoothed vs. unsmoothed curves

### Smoothing Algorithm
The smoothing process uses cubic Bezier curves:
```cpp
// Create smooth curve from points
if(ui->chkbox->isChecked()) {
    SmoothCurveCreator curve(Points);
    painter.drawPath(curve.path);
}
```

## Visual Interface

### Coordinate System
- Origin at center of window
- X-axis spans window width
- Y-axis spans window height
- Points plotted relative to origin

### Point Display
- Each point shown as small circle
- Size: 10x10 pixels
- Centered on exact coordinates
- Connected by lines or curves

## Interactive Features

### Real-time Updates
- Curve updates immediately on type selection
- Smoothing toggle provides instant feedback
- Window resizing adjusts coordinate system

### Curve Comparison
1. Generate desired curve type
2. Toggle smoothing on/off
3. Observe differences between:
   - Original point connections
   - Smoothed Bezier curves

## Example Workflows

### Creating a Smooth Random Curve
1. Launch application
2. Click "Random Curve" button
3. Enable smoothing checkbox
4. Observe generated smooth curve
5. Toggle smoothing to compare

### Visualizing Mathematical Functions
1. Choose desired function type:
   - Sine wave
   - Logarithmic
   - Exponential
2. Enable smoothing for continuous curve
3. Disable smoothing to see control points

## Tips and Best Practices

### Performance Optimization
- Window size affects point density
- Larger windows create more points
- Smoothing calculation time increases with points

### Visual Analysis
- Use smoothing toggle to understand:
  - Point distribution
  - Curve characteristics
  - Bezier curve effects

### Common Operations
- Switch between curve types to compare
- Toggle smoothing for different views
- Resize window to adjust scale
