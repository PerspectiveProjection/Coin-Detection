# Coin-Detection
An application to detects and counts coins.

# Introduction
The application first performs connected component labelling to the original image.
Next the areas, centroids and labels are added to a class Coin which represents each
coin detected in the picture. This vector of coins is then returned.

Next, a circular hough transform is applied to the original image.

