#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "sagin-helper.h"
#include "sagin-routing.h"

using namespace ns3;

void TxCallback(Ptr<const Packet> packet) {
    NS_LOG_UNCOND("Transmitting packet from UAV node to ground node");
}

void RxCallback(Ptr<const Packet> packet, const Address &srcAddress, const Address &dstAddress) {
    NS_LOG_UNCOND("Received packet at ground node from " << InetSocketAddress::ConvertFrom(srcAddress).GetIpv4());
}

void PrintNodeCounts(uint32_t numGroundNodes, uint32_t numUavNodes, uint32_t numSatelliteNodes) {
    NS_LOG_UNCOND("Number of ground nodes: " << numGroundNodes);
    NS_LOG_UNCOND("Number of UAV nodes: " << numUavNodes);
    NS_LOG_UNCOND("Number of satellite nodes: " << numSatelliteNodes);
}

double CalculateDistance(Ptr<Node> node1, Ptr<Node> node2) {
    Ptr<MobilityModel> mob1 = node1->GetObject<MobilityModel>();
    Ptr<MobilityModel> mob2 = node2->GetObject<MobilityModel>();
    return mob1->GetDistanceFrom(mob2);
}

void PrintPathsAndBestPath(NodeContainer groundNodes, NodeContainer uavNodes, NodeContainer satelliteNodes, uint32_t srcNode, std::string srcType, uint32_t dstNode, std::string dstType) {
    NS_LOG_UNCOND("Possible paths from " << srcType << " Node " << srcNode << " to " << dstType << " Node " << dstNode << " using aerial nodes:");
    double minDistance = std::numeric_limits<double>::max();
    std::string bestPath;
    
    Ptr<Node> src, dst;
    if (srcType == "ground") src = groundNodes.Get(srcNode);
    else if (srcType == "uav") src = uavNodes.Get(srcNode);
    else if (srcType == "satellite") src = satelliteNodes.Get(srcNode);

    if (dstType == "ground") dst = groundNodes.Get(dstNode);
    else if (dstType == "uav") dst = uavNodes.Get(dstNode);
    else if (dstType == "satellite") dst = satelliteNodes.Get(dstNode);

    for (uint32_t i = 0; i < groundNodes.GetN(); ++i) {
        for (uint32_t j = 0; j < uavNodes.GetN(); ++j) {
            for (uint32_t k = 0; k < satelliteNodes.GetN(); ++k) {
                double distance = CalculateDistance(src, uavNodes.Get(j)) +
                                  CalculateDistance(uavNodes.Get(j), dst);
                std::string path = "Path: " + srcType + " Node " + std::to_string(srcNode) + " -> UAV Node " + std::to_string(j) + " -> " + dstType + " Node " + std::to_string(dstNode);
                NS_LOG_UNCOND(path << " with distance: " << distance);
                if (distance < minDistance) {
                    minDistance = distance;
                    bestPath = path;
                }
            }
        }
    }
    NS_LOG_UNCOND("Best path: " << bestPath);
    NS_LOG_UNCOND("Reason: This path was chosen because it has the shortest distance of " << minDistance);
}

int main(int argc, char *argv[]) {
    // Set up default values for the simulation
    uint32_t numGroundNodes = 5;
    uint32_t numUavNodes = 2;
    uint32_t numSatelliteNodes = 1;
    double simulationTime = 10.0; // seconds
    uint32_t packetSize = 1024; // bytes
    double minBandwidth = 5.0; // Mbps
    double maxDelay = 2.0; // ms
    uint32_t srcNode = 1; // Set source node index here
    std::string srcType = "ground"; // Set source node type here (ground/uav/satellite)
    uint32_t dstNode = 0; // Set destination node index here
    std::string dstType = "satellite"; // Set destination node type here (ground/uav/satellite)
    std::string aerialNodeType = "haps"; // Set aerial node type here (uav/balloon/haps)
    std::string spaceNodeType = "leo"; // Set space node type here (leo/meo/geo)

    CommandLine cmd;
    cmd.AddValue("numGroundNodes", "Number of ground nodes", numGroundNodes);
    cmd.AddValue("numUavNodes", "Number of UAV nodes", numUavNodes);
    cmd.AddValue("numSatelliteNodes", "Number of satellite nodes", numSatelliteNodes);
    cmd.AddValue("simulationTime", "Simulation time in seconds", simulationTime);
    cmd.AddValue("packetSize", "Size of the packet in bytes", packetSize);
    cmd.AddValue("minBandwidth", "Minimum link bandwidth in Mbps", minBandwidth);
    cmd.AddValue("maxDelay", "Maximum tolerable delay in ms", maxDelay);
    cmd.AddValue("srcNode", "Source node number", srcNode);
    cmd.AddValue("srcType", "Source node type (ground/uav/satellite)", srcType);
    cmd.AddValue("dstNode", "Destination node number", dstNode);
    cmd.AddValue("dstType", "Destination node type (ground/uav/satellite)", dstType);
    cmd.AddValue("aerialNodeType", "Type of aerial node (uav/balloon/haps)", aerialNodeType);
    cmd.AddValue("spaceNodeType", "Type of space node (leo/meo/geo)", spaceNodeType);
    cmd.Parse(argc, argv);

    // Enable logging
    LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);

    // Create nodes
    NodeContainer groundNodes, aerialNodes, spaceNodes;
    groundNodes.Create(numGroundNodes);
    aerialNodes.Create(numUavNodes); // Assuming numUavNodes is used for aerial nodes
    spaceNodes.Create(numSatelliteNodes);

    // Dynamically set source and destination nodes
    Ptr<Node> src, dst;
    if (srcType == "ground" && srcNode < numGroundNodes) src = groundNodes.Get(srcNode);
    else if ((srcType == "uav" || srcType == "balloon" || srcType == "haps") && srcNode < numUavNodes) src = aerialNodes.Get(srcNode);
    else if ((srcType == "leo" || srcType == "meo" || srcType == "geo") && srcNode < numSatelliteNodes) src = spaceNodes.Get(srcNode);
    else {
        NS_FATAL_ERROR("Invalid source node type or index");
    }

    if (dstType == "ground" && dstNode < numGroundNodes) dst = groundNodes.Get(dstNode);
    else if ((dstType == "uav" || dstType == "balloon" || dstType == "haps") && dstNode < numUavNodes) dst = aerialNodes.Get(dstNode);
    else if ((dstType == "leo" || dstType == "meo" || dstType == "geo") && dstNode < numSatelliteNodes) dst = spaceNodes.Get(dstNode);
    else if (dstType == "satellite" && dstNode < numSatelliteNodes) dst = spaceNodes.Get(dstNode);
    else {
        NS_FATAL_ERROR("Invalid destination node type or index");
    }

    // Print the number of nodes
    PrintNodeCounts(numGroundNodes, numUavNodes, numSatelliteNodes);

    // Set up mobility models
    MobilityHelper groundMobility, aerialMobility, spaceMobility;
    groundMobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    groundMobility.Install(groundNodes);

    aerialMobility.SetMobilityModel("ns3::ConstantVelocityMobilityModel");
    aerialMobility.Install(aerialNodes);

    spaceMobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    spaceMobility.Install(spaceNodes);

    // Set initial positions
    for (uint32_t i = 0; i < numGroundNodes; ++i) {
        Ptr<ConstantPositionMobilityModel> pos = groundNodes.Get(i)->GetObject<ConstantPositionMobilityModel>();
        pos->SetPosition(Vector(i * 500.0, 0.0, 0.0)); // Urban, suburban, or rural configurations
    }
    for (uint32_t i = 0; i < numUavNodes; ++i) {
        Ptr<ConstantVelocityMobilityModel> pos = aerialNodes.Get(i)->GetObject<ConstantVelocityMobilityModel>();
        pos->SetPosition(Vector(i * 1000.0, 0.0, 1000.0)); // UAV altitude typically ranges from 100-3000 m
        pos->SetVelocity(Vector(5.0, 0.0, 0.0));
    }
    for (uint32_t i = 0; i < numSatelliteNodes; ++i) {
        Ptr<ConstantPositionMobilityModel> pos = spaceNodes.Get(i)->GetObject<ConstantPositionMobilityModel>();
        pos->SetPosition(Vector(i * 10000.0, 0.0, 2000000.0)); // LEO satellites at 500-2000 km
    }

    // Install Internet stack
    InternetStackHelper internet;
    internet.Install(groundNodes);
    internet.Install(aerialNodes);
    internet.Install(spaceNodes);

    // Set up Point-to-Point channel
    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", DataRateValue(DataRate(minBandwidth * 1e6)));
    p2p.SetChannelAttribute("Delay", TimeValue(MilliSeconds(maxDelay)));

    // Connect nodes
    NetDeviceContainer devices;
    for (uint32_t i = 0; i < numGroundNodes - 1; ++i) {
        devices.Add(p2p.Install(groundNodes.Get(i), groundNodes.Get(i + 1)));
    }
    for (uint32_t i = 0; i < numUavNodes - 1; ++i) {
        devices.Add(p2p.Install(aerialNodes.Get(i), aerialNodes.Get(i + 1)));
    }
    for (uint32_t i = 0; i < numSatelliteNodes - 1; ++i) {
        devices.Add(p2p.Install(spaceNodes.Get(i), spaceNodes.Get(i + 1)));
    }

    // Assign IP addresses
    Ipv4AddressHelper ipv4;
    ipv4.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer groundInterfaces;
    groundInterfaces = ipv4.Assign(devices.Get(0));

    ipv4.SetBase("10.1.2.0", "255.255.255.0");
    Ipv4InterfaceContainer aerialInterfaces;
    aerialInterfaces = ipv4.Assign(devices.Get(1));

    ipv4.SetBase("10.1.3.0", "255.255.255.0");
    Ipv4InterfaceContainer spaceInterfaces;
    spaceInterfaces = ipv4.Assign(devices.Get(2));

    // Set up application
    uint16_t port = 9;
    UdpEchoServerHelper echoServer(port);
    ApplicationContainer serverApps;
    ApplicationContainer clientApps;

    if (dstType == "ground") {
        serverApps = echoServer.Install(groundNodes.Get(dstNode));
    } else if (dstType == "uav" || dstType == "balloon" || dstType == "haps") {
        serverApps = echoServer.Install(aerialNodes.Get(dstNode));
    } else if (dstType == "satellite" || dstType == "leo" || dstType == "meo" || dstType == "geo") {
        serverApps = echoServer.Install(spaceNodes.Get(dstNode));
    }
    serverApps.Start(Seconds(1.0));
    serverApps.Stop(Seconds(simulationTime));

    Ipv4Address dstAddress;
    if (dstType == "ground" && dstNode < groundInterfaces.GetN()) {
        dstAddress = groundInterfaces.GetAddress(dstNode);
    } else if (dstType == "uav" && dstNode < aerialInterfaces.GetN()) {
        dstAddress = aerialInterfaces.GetAddress(dstNode);
    } else if (dstType == "satellite" && dstNode < spaceInterfaces.GetN()) {
        dstAddress = spaceInterfaces.GetAddress(dstNode);
    } else if ((dstType == "leo" || dstType == "meo" || dstType == "geo") && dstNode < spaceInterfaces.GetN()) {
        dstAddress = spaceInterfaces.GetAddress(dstNode);
    } else {
        NS_FATAL_ERROR("Invalid destination node type or index for IP address assignment");
    }

    UdpEchoClientHelper echoClient(dstAddress, port);
    echoClient.SetAttribute("MaxPackets", UintegerValue(1));
    echoClient.SetAttribute("Interval", TimeValue(Seconds(1.0)));
    echoClient.SetAttribute("PacketSize", UintegerValue(packetSize));

    if (srcType == "ground") {
        clientApps = echoClient.Install(groundNodes.Get(srcNode));
    } else if (srcType == "uav") {
        clientApps = echoClient.Install(aerialNodes.Get(srcNode));
    } else if (srcType == "satellite") {
        clientApps = echoClient.Install(spaceNodes.Get(srcNode));
    }
    clientApps.Start(Seconds(2.0));
    clientApps.Stop(Seconds(simulationTime));

    // Add tracing to show packet transfer
    Config::ConnectWithoutContext("/NodeList/*/ApplicationList/*/$ns3::UdpEchoClient/Tx", MakeCallback(&TxCallback));
    Config::ConnectWithoutContext("/NodeList/*/ApplicationList/*/$ns3::UdpEchoServer/RxWithAddresses", MakeCallback(&RxCallback));

    // Print paths and best path
    PrintPathsAndBestPath(groundNodes, aerialNodes, spaceNodes, srcNode, srcType, dstNode, dstType);

    // Run simulation
    Simulator::Run();
    Simulator::Destroy();

    return 0;
}