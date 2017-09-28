Programming 2 (Images)

==========================================================

Files you will modify:
   imageutil.c0       - Skeleton image helper functions

Files you won't modify:
   remove-red.c0      - You can modify this to respect the pixel/imageutil
                        interfaces if you'd like
   remove-red-main.c0 - Runs remove_red()
   remove-red-test.c0 - Some unit tests for remove_red()
   rotate-main.c0     - Runs rotate() 
   blur-main.c0       - Runs blur()

Files that don't exist yet:
   pixel.c0           - Copy this over from Programming 1 (Pixels)
   rotate.c0          - Task 2
   blur.c0            - Task 3
   imageutil-test.c0  - test your imageutil.c0 (optional)
   rotate-test.c      - test your rotate.c0 (optional)
   blur-test.c0       - test your blur.c0 (optional)
   
Data:
   blur-slightly-mask.txt - 3x3 blur
   blur-mask.txt - 5x5 blur
   images/g5.png
   images/g5-remove-red.png - result of remove_red()
   images/carnegie.png
   images/carnegie-rotate.png - result of rotate()
   images/scs.png
   images/scs-blur-slightly.png - result of blur() with blur-slightly-mask.txt
   images/scs-blur.png - result of blur() with mask blur-mask.txt

==========================================================

Compiling your imageutil tests:
   % cc0 -d -w -o imageutil-test imageutil.c0 imageutil-test.c0
   % ./imageutil-test

Compiling remove-red:
   % cc0 -d -w -o remove-red-test pixel.c0 imageutil.c0 remove-red.c0 remove-red-test.c0
   % ./remove-red-test

   % cc0 -d -w -o remove-red pixel.c0 imageutil.c0 remove-red.c0 remove-red-main.c0
   % ./remove-red -i images/g5.png -o images/g5-my-output.png 
       (This creates the output file images/g5-my-output.png. If you
        left off the "-o images/g5-my-output.png" part, the output
        file would be called images/g5_remove-red.png.)
   % imagediff -i images/g5-remove-red.png -j images/g5-my-output.png

       (This compares the file images/g5-remove-red.png, which was
        handed out as part of the assignment, with
        images/g5-my-output.png, which you just created.)

Compiling rotate:
   % cc0 -d -w -o rotate-test pixel.c0 imageutil.c0 rotate.c0 rotate-test.c0
   % ./rotate-test

   % cc0 -d -w -o rotate pixel.c0 imageutil.c0 rotate.c0 rotate-main.c0
   % ./rotate -i images/carnegie.png -o images/carnegie-my-output.png
       (This creates the output file images/carnegie-my-output.png. If
        you left off the "-o images/carnegie-my-output.png" part, the
        output file would be called images/carnegie_rotate.png.)
   % imagediff -i images/carnegie-rotate.png -j images/carnegie-my-output.png
       (This compares the file images/carnegie-rotate.png, which was
        handed out as part of the assignment, with
        images/carnegie-my-output.png, which you just created.)
 
Compiling blur:
   % cc0 -d -w -o blur-test pixel.c0 imageutil.c0 blur.c0 blur-test.c0
   % ./blur-test

   % cc0 -d -w -o blur pixel.c0 imageutil.c0 blur.c0 blur-main.c0
   % ./blur -i images/scs.png -o images/scs-my-output.png -m blur-mask.txt
       (This creates the output file images/scs-my-output.png. If you
        left off the "-o images/scs-my-output.png" part, the output
        file would be called images/scs_blur.png.)
   % imagediff -i images/scs-blur.png -j images/scs-my-output.png

==========================================================

Submitting with Andrew handin script:
   % handin hw2 imageutil.c0 rotate.c0 blur.c0 manipulate.c0

Creating a tarball to submit with Autolab web interface:
   % tar -czvf hw2sol.tgz imageutil.c0 rotate.c0 blur.c0 manipulate.c0

On autolab: https://autolab.cs.cmu.edu/15122-f13/images
