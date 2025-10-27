# mruby-clay

mruby bindings for the [CLAY](https://github.com/nicbarker/clay) library

# Development

To setup the repository locally:

```
  git clone git@github.com:AlexB52/mruby-clay.git
  cd mruby-clay 
  git submodule init
  git pull --recurse-submodules
  bin/build clean all
```

## Dependencies

* clay: 0.14
* 

Note: we have an extra commit on the Clay repository to add background colors to borders and text. Apply it with `git apply background-color-patch.txt`

## Build

Building mruby with mruby clay. The command is a wrapper of the Rake tasks located in mrucy folder.

      bin/build
      bin/build clean all # for a complete fresh build

## Test

After a building successfully mruby with mruby-clay

    rake mtest

## Examples

To run examples after mruby-clay is built successfully

    bin/run examples/hello_world.rb

## Troubleshooting

To remove the error message `mirb(19106,0x7ff85a248bc0) malloc: nano zone abandoned due to inability to reserve vm space.`

    export MallocNanoZone=0 

## Limitations

Here are some limitations of the mruby-clay bindings

  * Clay_Hovered: Currently Clay.hovered? is not supported inside the ui layout definition but only in the block