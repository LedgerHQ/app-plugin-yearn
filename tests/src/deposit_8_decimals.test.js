import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu, genericTx } from './test.fixture';
import { ethers } from "ethers";

const contractAddr = "0xA696a63cc78DfFa1a63E9E50587C197387FF6C7E";
const AMOUNT_TO_DEPOSIT = 2_12345678;
const BASE_SCREENS_S = (1 + 1 + 1 + 3 + 1) //YEARN + AMOUNT + GAS_FEES + VAULT + APPROVE
const BASE_SCREENS_X = (1 + 1 + 1 + 1 + 1) //YEARN + AMOUNT + GAS_FEES + VAULT + APPROVE

// Nanos S test
test('[Nano S] Deposit Tokens', zemu("nanos", async (sim, eth) => {
  const contract = new ethers.Contract(contractAddr, ['function deposit(uint256)']);
  const {data} = await contract.populateTransaction.deposit(AMOUNT_TO_DEPOSIT);
  let unsignedTx = genericTx;
  unsignedTx.to = contractAddr;
  unsignedTx.data = data;

  const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);
  const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanos_deposit', [BASE_SCREENS_S, 0]);
  await tx;
}));

test('[Nano X] Deposit Tokens', zemu("nanox", async (sim, eth) => {
  const contract = new ethers.Contract(contractAddr, ['function deposit(uint256)']);
  const {data} = await contract.populateTransaction.deposit(AMOUNT_TO_DEPOSIT);

  let unsignedTx = genericTx;
  unsignedTx.to = contractAddr;
  unsignedTx.data = data;

  const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);
  const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

  await waitForAppScreen(sim);
  await sim.navigateAndCompareSnapshots('.', 'nanox_deposit', [BASE_SCREENS_X, 0]);
  await tx;
}));
