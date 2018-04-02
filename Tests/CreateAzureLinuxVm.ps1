param
(
    [Parameter(Mandatory = $true)]
    [String] $omsWorkspaceId,

    [Parameter(Mandatory = $true)]
    [String] $omsWorkspaceKey
)

# Variables for common values
$resourceGroup = "autotestoms"
$location = "eastus"
$vmName = "autotestoms-1"
$subnetName = "autotestoms-subnet"
$virtualNetworkName = "autotestoms-vnet"
$dnsName = "autotestoms-dns-$(Get-Random)"
$networkSecurityRuleConfigName = "autotestoms-netsecurityrule-ssh"
$networkSecurityGroupName = "autotestoms-netsecuritygroup"
$networkInterfaceName = "autotestoms-nic"
<#
# Definer user name and blank password
$cred = Get-Credential
$username = $cred.UserName

# Create a resource group
New-AzureRmResourceGroup -Name $resourceGroup -Location $location

# Create a subnet configuration
$subnetConfig = New-AzureRmVirtualNetworkSubnetConfig -Name $subnetName -AddressPrefix 192.168.1.0/24

# Create a virtual network
$vnet = New-AzureRmVirtualNetwork -ResourceGroupName $resourceGroup -Location $location -Name $virtualNetworkName -AddressPrefix 192.168.0.0/16 -Subnet $subnetConfig

# Create a public IP address and specify a DNS name
$pip = New-AzureRmPublicIpAddress -ResourceGroupName $resourceGroup -Location $location -Name $dnsName -AllocationMethod Static -IdleTimeoutInMinutes 4

# Create an inbound network security group rule for port 22
$nsgRuleSSH = New-AzureRmNetworkSecurityRuleConfig -Name $networkSecurityRuleConfigName  -Protocol Tcp -Direction Inbound -Priority 1000 -SourceAddressPrefix * -SourcePortRange * -DestinationAddressPrefix * -DestinationPortRange 22 -Access Allow

# Create a network security group
$nsg = New-AzureRmNetworkSecurityGroup -ResourceGroupName $resourceGroup -Location $location -Name $networkSecurityGroupName -SecurityRules $nsgRuleSSH

# Create a virtual network card and associate with public IP address and NSG
$nic = New-AzureRmNetworkInterface -Name $networkInterfaceName -ResourceGroupName $resourceGroup -Location $location -SubnetId $vnet.Subnets[0].Id -PublicIpAddressId $pip.Id -NetworkSecurityGroupId $nsg.Id

# Create a virtual machine configuration
$vmConfig = New-AzureRmVMConfig -VMName $vmName -VMSize Standard_D1 | `
Set-AzureRmVMOperatingSystem -Linux -ComputerName $vmName -Credential $cred | `
Set-AzureRmVMSourceImage -PublisherName Canonical -Offer UbuntuServer -Skus '16.04-LTS' -Version latest | `
Add-AzureRmVMNetworkInterface -Id $nic.Id

# Configure SSH Keys
# $sshPublicKey = Get-Content "$env:USERPROFILE\.ssh\id_rsa.pub"
# Add-AzureRmVMSshPublicKey -VM $vmconfig -KeyData $sshPublicKey -Path "/home/$username/.ssh/authorized_keys"

# Create a virtual machine
New-AzureRmVM -ResourceGroupName $resourceGroup -Location $location -VM $vmConfig
#>
# Add customer script extension to machine
$omsAgentPackageUri = "https://github.com/Microsoft/OMS-Agent-for-Linux/releases/download/OMSAgent_GA_v1.4.4-210/omsagent-1.4.4-210.universal.x64.sh"
$testRunnerUri = "https://raw.githubusercontent.com/kwirkykat/PowerShell-DSC-for-Linux/AddTestAutomation/Tests/OMSTestRunner.py"
$omsAgentPackageLocation = "omsagent-1.4.4-210.universal.x64.sh"

$customScriptExtensionProtectedSettings = @{
    commandToExecute = "sudo python ./OMSTestRunner.py $omsAgentPackageLocation $omsWorkspaceID $omsWorkspaceKey"
}
$customScriptExtensionSettings = @{
    fileUris = @($omsAgentPackageUri, $testRunnerUri)
}

$customScriptExtensionName = 'autotestomsrunner'
Set-AzureRmVMExtension -Publisher Microsoft.Azure.Extensions -ResourceGroupName $resourceGroup -Name $customScriptExtensionName -VMName $vmName -Settings $customScriptExtensionSettings -ProtectedSettings $customScriptExtensionProtectedSettings -Location $location -ExtensionType 'CustomScript' -TypeHandlerVersion "2.0"
Get-AzureRmVMExtension -ResourceGroupName $resourceGroup -VMName $vmName -Name $customScriptExtensionName
