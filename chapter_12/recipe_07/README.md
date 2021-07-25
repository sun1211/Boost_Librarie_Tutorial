# Manipulating images

At step 2, we are describing the types of images we wish to work with. These images are gray images with 8 and 16 bits per pixel and RGB pictures with 8 bits per pixel.

The boost::gil::any_image<img_types> class is a kind of Boost.Variant that may hold an image of one of the img_types variables. As you may have already guessed, boost::gil::png_read_image reads images into image variables.

The boost::gil::apply_operation function at step 4 is almost equal to boost::apply_visitor from the Boost.Variant library. Note the usage of view(source). The boost::gil::view function constructs a light wrapper around the image that interprets it as a two-dimensional array of pixels.

Do you remember that for Boost.Variant we were deriving visitors from boost::static_visitor? When we are using GIL's version of variant, we need to make a result_type typedef inside visitor. You can see it in step 6.

A little bit of theory: images consist of points called pixels. One image has pixels of the same type. However, pixels of different images may differ in channels count and color bits for a single channel. A channel represents a primary color. In the case of an RGB image, we have a pixel consisting of three channels - red, green, and blue. In the case of a gray image, we have a single channel representing gray.

Back to our image. At step 2, we described the types of images we wish to work with. At step 3, one of those image types is read from file and stored in the source variable. At step 4, the operator() method of the negate visitor is instantiated for all image types.

At step 7, we can see how to get the channel type from the image view.

At step 8, we iterate through pixels and channels and negate them. Negation is done via max_val - source(x, y)[c] and the result is written back to the image view.

We write an image back at step 5.

C++17 has no built-in methods to work with images. There is ongoing work to add 2D drawing to the C++ standard library, though it's a kind of orthogonal functionality.

The Boost.GIL library is fast and efficient. The compilers optimize its code well and we may even help the optimizer using some of the Boost.GIL methods to unroll loops. But this chapter talks about only some of the library basics, so it is time to stop.

*Notes:* this example need -lpng to run, do not show here


