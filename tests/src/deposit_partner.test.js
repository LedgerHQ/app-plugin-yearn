import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu, genericTx, SPECULOS_ADDRESS, RANDOM_ADDRESS, txFromEtherscan} from './test.fixture';
import { ethers } from "ethers";

const BASE_SCREENS_S = (1 + 1 + 1 + 1 + 1) //YEARN + AMOUNT + VAULT + GAS_FEES + APPROVE
const BASE_SCREENS_X = (1 + 1 + 1 + 1 + 1) //YEARN + AMOUNT + VAULT + GAS_FEES + APPROVE

const contractAddr = "0x8ee392a4787397126c163cb9844d7c447da419d8";
const pluginName = "yearn";
const abi_path = `../${pluginName}/abis/` + contractAddr + '.json';
const abi = require(abi_path);

const contract = new ethers.Contract(contractAddr, abi);
const PARTNER_ID_ADDR = "0xB8c93dF4E1e6b1097889554D9294Dfb42814063a";
const DAI_CONTRACT_ADDR = "0xdA816459F1AB5631232FE5e97a05BBBb94970c95";

const AMOUNT_TO_DEPOSIT = '60000000000000000000'; // 60

test('[Nano S] Deposit Tokens with Partner contract', zemu("nanos", async (sim, eth) => {
  
  const {data} = await contract.populateTransaction['deposit(address,address,uint256)'](
    DAI_CONTRACT_ADDR, PARTNER_ID_ADDR, AMOUNT_TO_DEPOSIT
  );

  let unsignedTx = genericTx;
  unsignedTx.to = contractAddr;
  unsignedTx.data = data;
  const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);
  const tx = eth.signTransaction("44'/60'/0'/0",serializedTx);

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanos_deposit_partner', [BASE_SCREENS_S, 0]);
  await tx;
}));

test('[Nano X] Deposit Tokens with Partner contract', zemu("nanox", async (sim, eth) => {
  const {data} = await contract.populateTransaction['deposit(address,address,uint256)'](
    DAI_CONTRACT_ADDR, PARTNER_ID_ADDR, AMOUNT_TO_DEPOSIT
  );

  let unsignedTx = genericTx;
  unsignedTx.to = contractAddr;
  unsignedTx.data = data;
  const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);
  const tx = eth.signTransaction("44'/60'/0'/0",serializedTx);

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanox_deposit_partner', [BASE_SCREENS_X, 0]);
  await tx;
}));

test('[Nano SP] Deposit Tokens with Partner contract', zemu("nanosp", async (sim, eth) => {
  const {data} = await contract.populateTransaction['deposit(address,address,uint256)'](
    DAI_CONTRACT_ADDR, PARTNER_ID_ADDR, AMOUNT_TO_DEPOSIT
  );

  let unsignedTx = genericTx;
  unsignedTx.to = contractAddr;
  unsignedTx.data = data;
  const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);
  const tx = eth.signTransaction("44'/60'/0'/0",serializedTx);

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanox_deposit_partner', [BASE_SCREENS_X, 0]);
  await tx;
}));
