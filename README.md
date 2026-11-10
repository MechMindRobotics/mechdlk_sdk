# Mech-DLK SDK 3.0.0 Examples

Mech-DLK SDK enables you to run inference with models exported from Mech-DLK in your own applications. This repository contains the C++, C#, and Python examples included in the Mech-DLK SDK 3.0.0 installer.

[Download Mech-DLK SDK](https://downloads.mech-mind.com/?tab=tab-dlk-sdk) · [SDK 3.0.0 documentation](https://docs.mech-mind.net/en/dlk-sdk-manual/3.0.0/dlk-sdk.html) · [Release notes](https://docs.mech-mind.net/en/dlk-sdk-manual/3.0.0/release-notes.html)

## Get started

1. **Install Mech-DLK SDK 3.0.0.** Check the system requirements, install the SDK, and activate the software license for inference. [Installation guide](https://docs.mech-mind.net/en/dlk-sdk-manual/3.0.0/software-installation.html)
2. **Choose a basic inference example.** Use the SDK libraries and sample resources from the matching installation. Follow the guide for your language to configure the required dependencies and run the example. [Sample usage guide](https://docs.mech-mind.net/en/dlk-sdk-manual/3.0.0/samples/samples.html)
3. **Run inference with your model.** Export a compatible model package from Mech-DLK and use the inference tutorial to load the model, prepare an input image, and retrieve the results. [Inference tutorial](https://docs.mech-mind.net/en/dlk-sdk-manual/3.0.0/infer-tutorial.html)

## Examples

- **[C++](cpp/examples/)** — Start with [basic inference](cpp/examples/basic/). The advanced examples cover multithreaded inference, OpenCV integration, and HALCON integration.
- **[C#](csharp/examples/)** — Start with the [basic Visual Studio solution](csharp/examples/basic/basic.sln). The advanced examples cover multithreaded inference, OpenCV, HALCON, and a [Windows Forms inference application](csharp/examples/advanced/infer_with_ui/).
- **[Python](python/examples/)** — Start with [basic_infer.py](python/examples/basic_infer.py). Additional scripts demonstrate multithreaded inference, OpenCV integration, and HALCON integration.

## Model compatibility

Mech-DLK SDK 3.0.0 supports inference with models exported from Mech-DLK 2.5.4 or later. It also supports multi-model packages exported from Mech-DLK 3.0.0. [SDK documentation](https://docs.mech-mind.net/en/dlk-sdk-manual/3.0.0/dlk-sdk.html) · [Release notes](https://docs.mech-mind.net/en/dlk-sdk-manual/3.0.0/release-notes.html)

## Support

For installation and runtime questions, see the [SDK FAQ](https://docs.mech-mind.net/en/dlk-sdk-manual/3.0.0/faq/faq.html) or visit the [Mech-Mind Community](https://community.mech-mind.com/).

## License

The examples in this repository are distributed under the [BSD 3-Clause License](LICENSE).
