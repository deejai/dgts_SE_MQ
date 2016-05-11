#SE MQ
##Messaging Prototype
Supported messaging systems: **RabbitMQ**

Supported CMake configurations: **Visual Studio 2015**
___
####Add to SE_MQ Properties -> Debugging -> Environment PATH variable:
%PathToSemqRoot%/build/Debug/lib;
%PathToSemqRoot%/ThirdParty/Windows.x64.vc.13/boost/1.60.0/Debug/bin;
%PathToSemqRoot%/ThirdParty/Windows.x64.vc.13/rabitmq-c//bin;
%PathToSemqRoot%/SE_MQ/ThirdParty/Windows.x64.vc.13/SimpleAmqpClient//bin;