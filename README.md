# ofxDepthCamera

Device-independent library for working with depth cameras, recording, playback, and streaming remotely

**This is a work in progress!** It's half-done (at best), so some stuff isn't implemented yes and the rest probably doesn't work :) Send a note if you're curious what this is about or want to help. More info coming soon.

## Motivation

There are [a](https://github.com/genekogan/ofxKinectProjectorToolkit) [lot](https://github.com/kylemcdonald/ofxVirtualKinect) [of](https://github.com/dasaki/ofxKinectBlobTracker) [addons](https://github.com/toyoshim/ofxRemoteKinect) for using the Kinect & openFrameworks. Recently I've been working with the KinectV2 on Windows, and ended up looking into, modifying, and sometimes rewriting these addons to work with `ofxKinectForWindows2`, or with `ofxMultiKinectV2` on Mac. Many of these addons don't use camera- or SDK-specific features – they are just using the depth & color images, and the registration between them. With [so](http://www.xbox.com/en-US/xbox-360/accessories/kinect) [many](http://www.xbox.com/en-US/xbox-one/accessories/kinect-for-xbox-one) [depth](http://click.intel.com/intel-realsense-developer-kit.html) [cameras](https://orbbec3d.com) [available](http://structure.io) [now](https://www.asus.com/3D-Sensor/), separating the functionality of useful addons from the dependency of a specific camera or platform, and providing a consistent API to get needed data from the camera, seemed like a Very Good Idea.

On top of that, being able to easily & seamlessly use multiple cameras together, record and play back in sync, and utilize directly-connected or remote cameras (on a different computer on the same LAN), is very attractive. And so this addon was born.

More thoughts are articulated in [this openFrameworks forum post](http://forum.openframeworks.cc/t/new-addon-ofxdepthcamera/20987).


## Setup

As mentioned, this is a work in progress, so hopefully this process gets simplified over time.

Clone this addon, including dependencies which are set up as submodules. The dependencies include ofxImageSequence, ofxImageSequencePlayback, and ofxImageSequenceRecorder, which have been templated to work with various types of ofPixels (including ofShortPixels needed for the 16-bit depth data):

```
git clone --recursive https://github.com/mattfelsen/ofxDepthCamera
```

If you've already cloned this repo without using `--recursive`, you can fetch all the submodules like so:

```
cd ofxDepthCamera
git submodule update --init
```

You will also need either [ofxLibwebsockets](https://github.com/labatrockwell/ofxLibwebsockets) or [ofxZmq](https://github.com/mattfelsen/ofxZmq/tree/vs2015-x64-precompiled-libs) if you are planning to use a remotely-connected camera and are streaming its data over the network:

```
git clone https://github.com/labatrockwell/ofxLibwebsockets
git clone https://github.com/mattfelsen/ofxZmq --branch vs2015-x64-precompiled-libs
```

## Usage

Use the projectGenerator to create a new project. As addons, select ofxDepthCamera and the standalone addon for the camera you're interested in using, i.e. ofxKinect, ofxKinectForWindows2, etc. If you plan on streaming data from a remote camera, also add either ofxLibwebsockets or ofxZmq.

Open your new project, and enable the adapter for the camera you're using by uncommenting the appropriate `#define` in `ofxDepthCamera.h`. For example, if you're using a Kinect v1 device, enable `#define OFX_DEPTH_CAMERA_KINECT`.

Finally, when you call `setup()` on your camera, you will also need to specify the the camera type. For example, if you're using a Kinect v1 device, you will call `device.setup<Kinect>()`. See the `example-basic` project, which includes examples & comments for a variety of cameras.

If you are using a remote camera, also be sure to enable the streaming method you prefer by enabling the proper `#define` at the top of `ofxDepthCamera/Sender.h` and `ofxDepthCamera/Receiver.h`

## Examples

There is an `example-basic` project which demonstrates switching between live playback, recording, playing recorded data (with folder drag & drop support), and streaming from a remote camera. To send data from a remote computer with a camera attached, use the `example-sender` project. You can switch between ofxLibwebsockets and ofxZmq with a `#define` in `ofxDepthCamera/Sender.h`
