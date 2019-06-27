<project xmlns="com.autoesl.autopilot.project" name="lenet5_prj" top="lenet5">
    <files>
        <file name="firmware/lenet5.cpp" sc="0" tb="false" cflags="-I/home/hlab/hikari/Repos/hls4ml-sheryl/nnet_utils -std=c++0x"/>
        <file name="../../lenet5_test.cpp" sc="0" tb="1" cflags=" -I/home/hlab/hikari/Repos/hls4ml-sheryl/nnet_utils  -std=c++0x"/>
        <file name="../../../../../../../../asap2/hikari/vivado_prj_quant_lstm/test_images" sc="0" tb="1" cflags=""/>
        <file name="../../firmware/weights" sc="0" tb="1" cflags=" "/>
    </files>
    <includePaths/>
    <libraryPaths/>
    <libraryFlag/>
    <Simulation argv="">
        <SimFlow name="csim" ldflags="" mflags="" clean="true" csimMode="0" lastCsimMode="0" compiler="true"/>
    </Simulation>
    <solutions xmlns="">
        <solution name="solution1" status="active"/>
    </solutions>
</project>

